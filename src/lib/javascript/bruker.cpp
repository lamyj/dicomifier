/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/bruker.h"

#include <iterator>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <odil/base64.h>
#include <v8.h>

#include "bruker/converters/pixel_data_converter.h"
#include "bruker/Directory.h"
#include "bruker/json_converter.h"
#include "javascript/common.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace javascript
{

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

v8::Handle<v8::Value>
convertPixelDataToDicom(v8::Arguments const & args)
{
    v8::HandleScope scope;

    v8::Handle<v8::Context> context = v8::Context::GetCurrent();
    v8::Handle<v8::Object> global = context->Global();

    v8::Handle<v8::Object> JSON =
        global->Get(v8::String::New("JSON"))->ToObject();
    v8::Handle<v8::Function> JSON_stringify =
        v8::Handle<v8::Function>::Cast(JSON->Get(v8::String::New("stringify")));
    auto object = args[0];
    v8::String::Utf8Value json_js(JSON_stringify->Call(JSON, 1, &object));

    std::istringstream json_text(std::string(*json_js, json_js.length()));
    Json::Value json;
    json_text >> json;


    try
    {
        auto const dataset = dicomifier::bruker::as_dataset(json);
        auto const conversion_info =
            dicomifier::bruker::convert_pixel_data_to_dicom(dataset);
        auto conversion_info_js = v8::Array::New(4);
        conversion_info_js->Set(0, v8::Null());
        conversion_info_js->Set(1, v8::Boolean::New(std::get<1>(conversion_info)));
        conversion_info_js->Set(2, v8::Number::New(std::get<2>(conversion_info)));
        conversion_info_js->Set(3, v8::Number::New(std::get<3>(conversion_info)));

        auto const & buffer = std::get<0>(conversion_info);
        auto const frames_count = args[1]->IntegerValue();
        if(frames_count != 0)
        {
            auto frames = v8::Array::New(frames_count);
            auto const frame_size = buffer.size()/frames_count;
            for(int i=0; i<frames_count; ++i)
            {
                std::string buffer_base64;
                buffer_base64.reserve(frame_size);
                odil::base64::encode(
                    buffer.begin()+i*frame_size, buffer.begin()+(i+1)*frame_size,
                    std::back_inserter(buffer_base64));
                frames->Set(
                    i, v8::String::New(buffer_base64.c_str(), buffer_base64.size()));
            }
            conversion_info_js->Set(0, frames);
        }
        else
        {
            std::string buffer_base64;
            buffer_base64.reserve(buffer.size());
            odil::base64::encode(
                buffer.begin(), buffer.end(), std::back_inserter(buffer_base64));
            conversion_info_js->Set(
                0, v8::String::New(buffer_base64.c_str(), buffer_base64.size()));
        }

        return scope.Close(conversion_info_js);
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }
}

}

}
