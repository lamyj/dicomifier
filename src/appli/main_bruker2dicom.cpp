/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <memory>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/program_options.hpp>

#include "bruker/converters/EnhanceBrukerDicom.h"
#include "bruker/Dataset.h"
#include "bruker/Directory.h"
#include "core/Logger.h"
#include "dicom/Dictionaries.h"

std::string to_series_number(std::string const & series,
                             std::string const & reconstruction)
{
    int seriesnum = boost::lexical_cast<int>(series) % 100;      // only 2 byte
    int reconum = boost::lexical_cast<int>(reconstruction) % 10000;  // only 4 bytes

    std::string mask = seriesnum < 10 ? "%01d%04d" : "%02d%04d";

    // Conversion: seriesnum (A) + reconum (B) => AABBBB
    char temp[7];
    memset(&temp[0], 0, 7);
    snprintf(&temp[0], 7, mask.c_str(), seriesnum, reconum);
    std::string series_number(temp);

    return series_number;
}

int main(int argc, char *argv[])
{
    std::string bruker_directory = "";
    std::string dicom_directory = "";
    std::string level = "ERROR";
    std::vector<std::string> series_and_reco;

    boost::program_options::options_description description("Options");
    description.add_options()
        ("help,h", "Print help messages")
        ("level,l", boost::program_options::value<std::string>(&level),
         "Log Level [DEBUG, INFO, WARNING, ERROR (default)]")
        ("reconstruction,r", boost::program_options::
            value<std::vector<std::string> >(&series_and_reco),
         "Series:Reconstruction to convert")
        ("subject", boost::program_options::
            value<std::string>(&bruker_directory)->required(),
         "Bruker directory")
        ("output", boost::program_options::
            value<std::string>(&dicom_directory)->required(),
         "Output directory to store DICOM files")
    ;

    boost::program_options::positional_options_description positionalOptions;
    positionalOptions.add("subject", 1);
    positionalOptions.add("output", 1);

    boost::program_options::variables_map variables_map;
    try
    {
        boost::program_options::store(boost::program_options::
                command_line_parser(argc, argv).options(description)
                .positional(positionalOptions).run(),
                                      variables_map);

        // --help option
        if ( variables_map.count("help")  )
        {
            std::cout << "Usage: bruker2dicom [OPTIONS] subject output \n"
                      << description << std::endl;
            return EXIT_SUCCESS;
        }

        boost::program_options::notify(variables_map);
    }
    catch(boost::program_options::error & e)
    {
        std::cerr << "ERROR: " << e.what() << "\n"
                  << "Usage: bruker2dicom [OPTIONS] subject output \n"
                  << description << std::endl;
        return EXIT_FAILURE;
    }

    dicomifier::InitializeLogger(level);
    
    /* TODO Private dictionary
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary(argv[2]);
    }*/
    // create Rule

    // Get the subject name
    boost::filesystem::path const subject =
        boost::filesystem::path(bruker_directory) / "subject";
    dicomifier::bruker::Dataset brukerdataset;
    brukerdataset.load(subject.c_str());

    std::string subject_name;
    if (brukerdataset.has_field("SUBJECT_name_string"))
    {
        subject_name =
                brukerdataset.get_field("SUBJECT_name_string").get_string(0);
    }
    else
    {
        if (brukerdataset.has_field("SUBJECT_id"))
        {
            subject_name = brukerdataset.get_field("SUBJECT_id").get_string(0);
        }
        else
        {
            subject_name = dicomifier::bruker::
                    EnhanceBrukerDicom::get_default_directory_name(
                        dicom_directory);
        }
    }

    // Get the study number
    boost::filesystem::path const dest =
        boost::filesystem::path(dicom_directory) / subject_name;
    std::string const study_number = dicomifier::bruker::
            EnhanceBrukerDicom::get_default_directory_name(dest);

    std::map<std::string, std::vector<std::string> > available_item =
            dicomifier::bruker::Directory::get_series_and_reco(bruker_directory);

    std::vector<std::string> items_to_process;

    if (series_and_reco.size() == 0)
    {
        // process all
        for (auto it = available_item.begin(); it != available_item.end(); ++it)
        {
            series_and_reco.push_back(it->first);
        }
    }

    for (std::string const item : series_and_reco)
    {
        // Create seriesNumber
        std::vector<std::string> series_reco;
        boost::split(series_reco, item, boost::is_any_of(":"),
                     boost::token_compress_on);

        std::string series = "";
        std::string reconstruction = "";
        if (series_reco.size() > 0)
        {
            series = series_reco[0];
        }
        if (series_reco.size() > 1)
        {
            reconstruction = series_reco[1];
        }

        // process all reconstruction
        if (available_item.find(series) != available_item.end())
        {
            if (reconstruction == "")
            {
                // process all reconstruction
                for (std::string const reco : available_item[series])
                {
                    items_to_process.push_back(to_series_number(series, reco));
                }
            }
            else
            {
                items_to_process.push_back(to_series_number(series,
                                                            reconstruction));
            }
        }
    }

    // Process
    for (std::string const series_number : items_to_process)
    {
        dicomifier::loggerInfo() << "Process seriesNumber: "
                                 << series_number << "...";

        auto rule = dicomifier::bruker::EnhanceBrukerDicom::New(
            bruker_directory, UID_MRImageStorage,
            dicom_directory, study_number, series_number);

        if (rule == NULL)
        {
            dicomifier::loggerError() << "Cannot create conversion rule";
            continue;
        }

        try
        {
            rule->run();

            dicomifier::loggerInfo() << "Done.";
        }
        catch (dicomifier::DicomifierException const & exc)
        {
            dicomifier::loggerError() << exc.what();
        }
        catch (std::exception const & unknown_exc)
        {
            dicomifier::loggerError() << "Unknown exception: "
                                      << unknown_exc.what();
        }
    }
            
    return EXIT_SUCCESS;
}
