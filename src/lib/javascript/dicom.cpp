/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/dicom.h"

#include <clocale>
#include <cmath>
#include <exception>
#include <fstream>
#include <iomanip>
#include <utility>

#include <boost/filesystem.hpp>
#include <odil/json_converter.h>
#include <odil/uid.h>
#include <odil/Reader.h>
#include <odil/registry.h>
#include <odil/Writer.h>
#include <v8.h>

#include "bruker/converters/EnhanceBrukerDicom.h"
#include "core/Logger.h"
#include "javascript/common.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace javascript
{

v8::Handle<v8::Value> read_dicom(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(
            v8::String::New("Missing input DICOM file path"));
    }

    auto const filename = as_scalar<std::string>(args[0]);

    std::ifstream stream(
        boost::filesystem::path(filename).c_str(),
        std::ios::in | std::ios::binary);

    std::pair<odil::DataSet, odil::DataSet> file;
    try
    {
        file = odil::Reader::read_file(stream);
    }
    catch(std::exception const & e)
    {
        dicomifier::loggerError()
            << "Could not read '" << filename << "': " << e.what() << "\n";
        return v8::Null();
    }

    if (!file.second.has(odil::registry::PixelData))
    {
        // ignore file
        return v8::Null();
    }

    try
    {
        auto const json_dicom_dataset = odil::as_json(file.second);

        std::stringstream script;
        script
            << "var dicom = " << json_dicom_dataset.toStyledString() << ";\n"
            << "dicom;";

        return JavascriptVM::run(script.str(), v8::Context::GetCurrent());
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

v8::Handle<v8::Value> write_dicom(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(
            v8::String::New("Missing Arguments for writeDICOM"));
    }

    try
    {
        // Get the JSON representation of the V8 data set.
        std::string json = as_scalar<std::string>(args[0]);

        // Parse it into a data set.
        Json::Value jsondataset;
        {
            Json::Reader reader;
            std::string old_locale = std::setlocale(LC_ALL, "C");
            reader.parse(json, jsondataset);
            std::setlocale(LC_ALL, old_locale.c_str());
        }

        auto const dataset = odil::as_dataset(jsondataset);

        // Get output file name
        auto const path_dcm = as_scalar<std::string>(args[1]);

        // Create directory if not exist
        boost::filesystem::path const destination(path_dcm);
        boost::filesystem::create_directories(destination.parent_path());

        std::string transfer_syntax = odil::registry::ExplicitVRLittleEndian;
        if(args.Length() == 3)
        {
            transfer_syntax = as_scalar<std::string>(args[2]);
        }

        std::ofstream stream(
            destination.c_str(), std::ios::out | std::ios::binary);
        odil::Writer::write_file(
            dataset, stream, odil::DataSet(), transfer_syntax,
            odil::Writer::ItemEncoding::UndefinedLength);
    }
    catch (std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

/**
 * @brief generate_dicom_filename
 * @param args
 * @return
 */
v8::Handle<v8::Value> generate_dicom_filename(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(v8::String::New("Missing input"));
    }

    v8::Local<v8::Object> object = args[0].As<v8::Object>();

    auto const outputdir = as_scalar<std::string>(object, "outputDir");
    auto const studyNumber = as_scalar<std::string>(object, "studyNumber");
    auto const seriesNumber = as_scalar<std::string>(object, "seriesNumber");

    std::string subject_name;
    if (object->Get(v8::String::New("SubjectName")).IsEmpty())
    {
        subject_name = bruker::EnhanceBrukerDicom::get_default_directory_name(outputdir);
    }
    else
    {
        subject_name = as_scalar<std::string>(object, "SubjectName");
    }

    auto const StudyDescription = as_scalar<std::string>(object, "StudyDescription");
    auto const SeriesDescription = as_scalar<std::string>(object, "SeriesDescription");

    // Study Directory: Counter + Study Description
    auto const study = bruker::EnhanceBrukerDicom::create_directory_name(
            8, studyNumber, StudyDescription);

    // Series Directory: Bruker Series directory + Series Description
    auto series_number = seriesNumber.substr(0, seriesNumber.size() == 6 ? 2 : 1);
    auto const series = bruker::EnhanceBrukerDicom::create_directory_name(
        8, series_number, SeriesDescription);

    // Instance file: Instance Number
    std::string instance = "1";
    if(as_scalar<bool>(object, "useFileFormat"))
    {
        auto const instance_number =
            int(as_scalar<double>(object, "InstanceNumber"));

        auto const images_in_acquistion =
            int(as_scalar<double>(object, "ImagesInAcquisition"));

        int const nbdigit = 1 + floor(log10(images_in_acquistion));

        std::ostringstream stream;
        stream << std::setw(nbdigit) << std::setfill('0') << instance_number;
        instance = stream.str();
    }

    // Destination: Subject/Study/Series/Instance
    boost::filesystem::path const destination =
        boost::filesystem::path(outputdir)
            /subject_name.c_str()/study/series/instance;
    boost::filesystem::create_directories(destination.parent_path());

    return v8::String::New(destination.c_str());
}

v8::Handle<v8::Value> generate_uid(v8::Arguments const &)
{
    auto const uid = odil::generate_uid();
    return v8::String::New(uid.c_str());
}

v8::Handle<v8::Value> getTagKeyword(v8::Arguments const & arguments)
{
    auto const tag_string = as_scalar<std::string>(arguments[0]);
    odil::Tag const tag(tag_string);
    try
    {
        auto const keyword = tag.get_name();
        return v8::String::New(keyword.c_str());
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }
}

}

}
