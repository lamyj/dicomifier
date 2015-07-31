/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EnhanceBrukerDicom.h"

#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Element.h>
#include <dcmtkpp/conversion.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/json_converter.h>

#include "bruker/Directory.h"
#include "bruker/json_converter.h"
#include "core/DicomifierException.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace bruker
{

EnhanceBrukerDicom::EnhanceBrukerDicom()
: _brukerDir(""), _SOPClassUID(""), _outputDir("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(
    std::string const & brukerDir, std::string const & sopclassuid,
    std::string const & outputDir, std::string const & studyNumber,
    std::string const & seriesNumber)
: _brukerDir(brukerDir), _SOPClassUID(sopclassuid), _outputDir(outputDir),
  _studyNumber(studyNumber), _seriesNumber(seriesNumber)
{
    // Nothing to do
}

EnhanceBrukerDicom::~EnhanceBrukerDicom()
{
    // Nothing to do
}

std::string const &
EnhanceBrukerDicom
::get_brukerDir() const
{
    return this->_brukerDir;
}

void
EnhanceBrukerDicom
::set_brukerDir(std::string const & brukerDir)
{
    this->_brukerDir = brukerDir;
}

std::string const &
EnhanceBrukerDicom
::get_SOPClassUID() const
{
    return this->_SOPClassUID;
}

void
EnhanceBrukerDicom
::set_SOPClassUID(std::string const & sopclassuid)
{
    this->_SOPClassUID = sopclassuid;
}

const std::string &
EnhanceBrukerDicom
::get_outputDir() const
{
    return this->_outputDir;
}

void
EnhanceBrukerDicom
::set_outputDir(const std::string &outputDir)
{
    this->_outputDir = outputDir;
}

void
EnhanceBrukerDicom
::run() const
{
    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(this->_brukerDir) )
    {
        throw DicomifierException("Input not a Directory: " + this->_brukerDir);
    }

    // Parse input bruker directory
    bruker::Directory brukerdirectory;
    brukerdirectory.load(this->_brukerDir);

    // Search corresponding Bruker Dataset
    if(!brukerdirectory.has_dataset(this->_seriesNumber))
    {
        throw DicomifierException("No such series");
    }

    auto const & brukerdataset = brukerdirectory.get_dataset(this->_seriesNumber);

    auto const sopclassuid = dicomifier::get_SOPClassUID_from_name(
        this->_SOPClassUID);
    if(sopclassuid == UID_MRImageStorage)
    {
        this->_create_mr_image_storage(brukerdataset);
    }
    else
    {
        throw DicomifierException("Unkown SOP Class UID '" + this->_SOPClassUID + "'");
    }
}

std::string
EnhanceBrukerDicom
::get_default_directory_name(const boost::filesystem::path &parentdirectory)
{
    if (! boost::filesystem::exists(parentdirectory))
    {
        return "1";
    }

    // Suppose we can't have more than 100000000 sub-directory
    for (int output = 1; output < 100000000; ++output)
    {
        std::stringstream pattern;
        pattern << output;

        bool find = true;

        boost::filesystem::directory_iterator it_end;
        for(boost::filesystem::directory_iterator it(parentdirectory.string());
            it != it_end; ++it)
        {
            std::string currentobj((*it).path().filename().c_str());
            if(currentobj.find(pattern.str().c_str()) == 0)
            {
                // we find a number already used
                find = false;
                break;
            }
        }
        if (find)
        {
            std::stringstream stream;
            stream << output;
            return stream.str();
        }
    }

    throw DicomifierException("Cannot find default directory name.");
}

boost::filesystem::path
EnhanceBrukerDicom
::get_destination_filename(dcmtkpp::DataSet const & dataset, bool usefileformat) const
{
    // Subject Directory: Patient's name or Patient's ID or Default value
    std::string subject_name;
    try
    {
        subject_name = dataset.as_string(dcmtkpp::registry::PatientName, 0);
    }
    catch(dcmtkpp::Exception)
    {
        try
        {
            subject_name = dataset.as_string(dcmtkpp::registry::PatientID, 0);
        }
        catch(dcmtkpp::Exception)
        {
            subject_name = EnhanceBrukerDicom::get_default_directory_name(
                this->_outputDir);
        }
    }

    // Study Directory: Counter + Study Description
    auto const study = this->create_directory_name(
            8, this->_studyNumber,
            dataset.as_string(dcmtkpp::registry::StudyDescription, 0));

    // Series Directory: Bruker Series directory + Series Description
    std::string series_description = "";
    // Series description is optional
    if (dataset.has(dcmtkpp::registry::SeriesDescription))
    {
        series_description = dataset.as_string(
            dcmtkpp::registry::SeriesDescription, 0);
    }
    auto series_number = boost::lexical_cast<std::string>(
        dataset.as_int(dcmtkpp::registry::SeriesNumber, 0));
    series_number = series_number.substr(0, series_number.size() == 6 ? 2 : 1);
    auto const series = this->create_directory_name(
        8, series_number, series_description);

    // Instance file: Instance Number
    std::string instance = "1";
    if (usefileformat)
    {
        auto const & instance_number = dataset.as_int(
            dcmtkpp::registry::InstanceNumber, 0);

        auto const images_in_acquistion = dataset.as_int(
            dcmtkpp::registry::ImagesInAcquisition, 0);

        int const nbdigit = 1 + floor(log10(images_in_acquistion));

        std::ostringstream stream;
        stream << std::setw(nbdigit) << std::setfill('0') << instance_number;
        instance = stream.str();
    }

    // Destination: Subject/Study/Series/Instance
    boost::filesystem::path const destination =
        boost::filesystem::path(this->_outputDir)
            /subject_name.c_str()/study/series/instance;
    boost::filesystem::create_directories(destination.parent_path());

    return destination;
}

void
EnhanceBrukerDicom
::_create_mr_image_storage(bruker::Dataset const & bruker_dataset) const
{
    javascript::JavascriptVM jsvm;

    auto const json_bruker_dataset = bruker::as_json(bruker_dataset);

    std::stringstream stream;
    stream << "dicomifier.inputs[0] = "
           << json_bruker_dataset.toStyledString() << ";";
    jsvm.run(stream.str());

    // use default file
    std::string script("/etc/dicomifier/script_bruker2dicom/frameIndexGenerator.js");

    std::string configuration_path("../configuration");
    char* value = getenv("DICOMIFIER_CONFIGURATION_DIR");
    if(value != NULL)
    {
        configuration_path = std::string(value);
    }

    std::stringstream mrimagestoragefile;
    mrimagestoragefile << configuration_path
                       << "/script_bruker2dicom/MRImageStorage.js";

    // if file exist locally
    if (boost::filesystem::exists(boost::filesystem::path(
            mrimagestoragefile.str())))
    {
        script = mrimagestoragefile.str();
    }

    // Execute script
    v8::Local<v8::Value> result = jsvm.run_file(script);
    v8::String::Utf8Value result2utf8(result);

    std::stringstream streamresult;
    streamresult << *result2utf8;

    auto number = boost::lexical_cast<unsigned int>(streamresult.str());
    for (unsigned int ds = 0; ds < number; ++ds)
    {
        std::stringstream streamscript;
        streamscript << "JSON.stringify(dicomifier.outputs[" << ds << "]);";
        auto dicom_json = jsvm.run(streamscript.str());
        v8::String::Utf8Value utf8(dicom_json);

        std::stringstream datasetstream;
        datasetstream << *utf8;
        Json::Value jsondataset;
        Json::Reader reader;
        std::string old_locale = std::setlocale(LC_ALL, "C");
        reader.parse(datasetstream, jsondataset);
        std::setlocale(LC_ALL, old_locale.c_str());

        dcmtkpp::DataSet const dicom_data_set = dcmtkpp::as_dataset(jsondataset);

        auto const destination = this->get_destination_filename(dicom_data_set);

        // write file
        auto * dcmtk_dataset = dynamic_cast<DcmDataset*>(
            dcmtkpp::convert(dicom_data_set));
        DcmFileFormat fileformat(dcmtk_dataset);
        OFCondition result = fileformat.saveFile(
            destination.c_str(), EXS_LittleEndianExplicit);
        if(result.bad())
        {
            throw DicomifierException(
                "Unable to save dataset: " + std::string(result.text()));
        }
    }
}

void
EnhanceBrukerDicom
::replace_unavailable_char(std::string &text)
{
    std::stringstream stream;
    stream << std::uppercase << text;
    text = stream.str();
    /* iterate over all charaters */
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        unsigned char c = text.at(i);
        if (std::isalpha(c) && std::islower(c))
        {
            text[i] = std::toupper(c);
        }
        else if ((c != '_') && !std::isdigit(c) && !std::isalpha(c))
        {
            // char not allowed, replace by _
            text[i] = '_';
        }
    }
}

std::string
EnhanceBrukerDicom
::create_directory_name(int sizemax, const std::string &prefix,
                        const std::string &suffix) const
{
    int size = sizemax - prefix.length() - 1; // 1 is for '_'
    std::string suffixmodif = suffix.substr(0, size);

    EnhanceBrukerDicom::replace_unavailable_char(suffixmodif);

    std::stringstream streamout;
    streamout << prefix << "_" << suffixmodif;
    return streamout.str();
}

} // namespace bruker

} // namespace dicomifier
