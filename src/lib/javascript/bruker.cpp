/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/bruker.h"

#include <string>

#include <boost/filesystem.hpp>
#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofstream.h>
#include <odil/DataSet.h>
#include <odil/Element.h>
#include <odil/json_converter.h>
#include <odil/registry.h>
#include <odil/uid.h>
#include <v8.h>

#include "bruker/converters/pixel_data_converter.h"
#include "bruker/Directory.h"
#include "bruker/json_converter.h"
#include "core/DicomifierException.h"
#include "javascript/common.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace javascript
{

void get_pixeldata_information(v8::Local<v8::Object> const & data_set,
                               std::string & pixel_data,
                               std::string & word_type,
                               std::string & byte_order,
                               int & frame_size)
{
    // Get PIXELDATA
    pixel_data = as_scalar<std::string>(data_set, "PIXELDATA", 0);

    // Get VisuCoreWordType
    word_type = as_scalar<std::string>(data_set, "VisuCoreWordType", 0);

    // Get VisuCoreByteOrder
    byte_order = as_scalar<std::string>(data_set, "VisuCoreByteOrder", 0);

    // Get VisuCoreSize
    auto const size_vector = as_vector<double>(data_set, "VisuCoreSize");
    if(size_vector.size() != 2)
    {
        throw DicomifierException("Invalid VisuCoreSize");
    }
    frame_size = int(size_vector[0])*int(size_vector[1]);
}

v8::Handle<v8::Value> load_pixel_data(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(v8::String::New("Missing BrukerDataset"));
    }
    if(args.Length() < 2)
    {
        return v8::ThrowException(v8::String::New("Missing frame number"));
    }

    std::string pixel_data;
    std::string word_type;
    std::string byte_order;
    int framesize;

    try
    {
        auto const data_set = args[0]->ToObject();
        if(data_set.IsEmpty())
        {
            throw DicomifierException("Data set is not an object");
        }
        get_pixeldata_information(
            data_set, pixel_data, word_type, byte_order, framesize);
    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }

    // Get the frame number
    auto numberOfFrame = as_scalar<double>(args[1]);
    if (args.Length() == 3)
    {
        // Get a flag to return all pixel data or a string for each frame
        if(as_scalar<bool>(args[2]))
        {
            framesize *= numberOfFrame;
            numberOfFrame = 1;
        }
    }

    // Create the array to return
    v8::Local<v8::Array> array = v8::Array::New(3);
    v8::Local<v8::Array> arrayimage = v8::Array::New(numberOfFrame);

    try
    {
        // Convert each frame in base64 String
        bruker::pixel_data_converter converter;
        for (unsigned int i = 0; i < numberOfFrame; ++i)
        {
            // Read pixel data file and get the Frame i
            converter(framesize, i, pixel_data, word_type, byte_order);

            auto const & pixel_data = converter.get_pixel_data();
            unsigned char const * data =
                reinterpret_cast<unsigned char const *>(&pixel_data[0]);
            OFStringStream stream;
            OFStandard::encodeBase64(stream, data, pixel_data.size());

            auto const & pixel_data_base64 = stream.str();

            // Store into the array
            arrayimage->Set(
                i, v8::String::New(
                    pixel_data_base64.c_str(), pixel_data_base64.size()));
        }

        array->Set(0, arrayimage);
        array->Set(1, v8::Number::New(converter.get_rescale_intercept()));
        array->Set(2, v8::Number::New(converter.get_rescale_slope()));
    }
    catch (std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return array;
}

v8::Handle<v8::Value> sort_pixel_data(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(v8::String::New("Missing input"));
    }

    try
    {
        std::string pixel_data;
        std::string word_type;
        std::string byte_order;
        int framesize;
        auto const data_set = args[0]->ToObject();
        if(data_set.IsEmpty())
        {
            throw DicomifierException("Data set is not an object");
        }
        get_pixeldata_information(data_set, pixel_data, word_type, byte_order,
                                  framesize);

        v8::Local<v8::Array> array = args[1].As<v8::Array>();

        dcmtkpp::Element element = dcmtkpp::Element(dcmtkpp::Value::Binary(),
                                                    dcmtkpp::VR::OW);
        bruker::pixel_data_converter converter;
        for (unsigned int i = 0; i < array->Length(); ++i)
        {
            int index = array->Get(i)->ToInt32()->Int32Value();
            converter(framesize, index, pixel_data, word_type, byte_order);
            auto const & pixel_data = converter.get_pixel_data();

            element.as_binary().insert(
                element.as_binary().end(), pixel_data.begin(), pixel_data.end());
        }

        dcmtkpp::DataSet dataset;
        dataset.add(dcmtkpp::registry::PixelData, element);

        // Convert to JSON
        Json::Value const json_dtset = dcmtkpp::as_json(dataset);

        return v8::String::New(
                    json_dtset["7fe00010"]["InlineBinary"].asCString());

    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch (std::exception const & otherexc)
    {
        return v8::ThrowException(v8::String::New(otherexc.what()));
    }
    return v8::Null();
}

v8::Handle<v8::Value> read_bruker_directory(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(
                v8::String::New("Missing Arguments for readBrukerDirectory"));
    }

    auto const bruker_path = as_scalar<std::string>(args[0]);

    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(bruker_path) )
    {
        std::stringstream error;
        error << "Input not a Directory: " << bruker_path;
        return v8::ThrowException(v8::String::New(error.str().c_str()));
    }

    try
    {
        // Parse input bruker directory
        bruker::Directory bruker_directory;
        bruker_directory.load(bruker_path);

        auto const series_number = as_scalar<std::string>(args[1]);

        // Search corresponding Bruker Dataset
        if(!bruker_directory.has_dataset(series_number))
        {
            return v8::ThrowException(v8::String::New("No such series"));
        }

        auto const & brukerdataset = bruker_directory.get_dataset(series_number);

        auto const json_bruker_dataset = dicomifier::bruker::as_json(brukerdataset);

        std::stringstream script;
        script << "var bruker = "
               << bruker::as_string(json_bruker_dataset) << ";\n" << "bruker;";

        return JavascriptVM::run(script.str(), v8::Context::GetCurrent());
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

}

}
