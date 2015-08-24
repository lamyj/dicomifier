/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <string>

#include <cxxabi.h>

#include <boost/program_options.hpp>

#include "core/DicomifierException.h"
#include "core/Logger.h"
#include "nifti/Dicom2Nifti.h"

std::string demangle(std::string const & name)
{
    std::string result;

#ifdef __GNUC__
    int status;
    auto data = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
    if(status == 0)
    {
        result = data;
        free(data);
    }
    else
    {
        result = name;
    }
#else
    result = name;
#endif

    return result;
}

int main(int argc, char *argv[])
{
    std::string dicom_directory = "";
    std::string nifti_directory = "";
    std::string level = "ERROR";

    boost::program_options::options_description description("Options");
    description.add_options()
        ("help,h", "Print help messages")
        ("level,l", boost::program_options::value<std::string>(&level),
         "Log Level [DEBUG, INFO, WARNING, ERROR (default)]")
        ("input", boost::program_options::
            value<std::string>(&dicom_directory)->required(),
         "Input directory containing DICOM files")
        ("output", boost::program_options::
            value<std::string>(&nifti_directory)->required(),
         "Output directory to store NIfTI files")
    ;

    boost::program_options::positional_options_description positionalOptions;
    positionalOptions.add("input", 1);
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
            std::cout << "Usage: dicom2nifti [OPTIONS] input output \n"
                      << description << std::endl;
            return EXIT_SUCCESS;
        }

        boost::program_options::notify(variables_map);
    }
    catch(boost::program_options::error & e)
    {
        std::cerr << "ERROR: " << e.what() << "\n"
                  << "Usage: dicom2nifti [OPTIONS] input output \n"
                  << description << std::endl;
        return EXIT_FAILURE;
    }

    dicomifier::InitializeLogger(level);

    auto rule = dicomifier::nifti::Dicom2Nifti::New(dicom_directory,
                                                    nifti_directory);

    if (rule == NULL)
    {
        dicomifier::loggerError() << "Cannot create conversion rule";
        return EXIT_FAILURE;
    }

    try
    {
        rule->run();
    }
    catch (dicomifier::DicomifierException const & exc)
    {
        dicomifier::loggerError() << exc.what()
                                  << " (" << demangle(typeid(exc).name()) << ")";
    }

    return EXIT_SUCCESS;
}
