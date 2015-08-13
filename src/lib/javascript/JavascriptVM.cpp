/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <string>

#include <boost/filesystem.hpp>

#include <dcmtkpp/json_converter.h>

#include "bruker/converters/pixel_data_converter.h"
#include "core/DicomifierException.h"
#include "dicom/Dictionaries.h"
#include "JavascriptVM.h"
#include "LoggerJS.h"

namespace dicomifier
{

namespace javascript
{

/***********************************
 *  Exposed functions              *
 **********************************/

v8::Handle<v8::Value> is_big_endian(v8::Arguments const & args)
{
    return v8::Boolean::New(endian::is_big_endian());
}

v8::Handle<v8::Value> generate_uid(v8::Arguments const & args)
{
    char buffer[128];
    dcmGenerateUniqueIdentifier(buffer, SITE_INSTANCE_UID_ROOT);
    std::string const uid(buffer);
    return v8::String::New(uid.c_str());
}

/**
 * @brief Get pixel data as base64 String
 * @param args: 3 arguments:
 *              - BrukerDataset (JSON bruker dataset,
 *              - Number of Frame (int),
 *              - All_data (bool)
 * @return array of base64 String
 */
v8::Handle<v8::Value> load_pixel_data(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        throw DicomifierException("Missing BrukerDataset");
    }
    if(args.Length() < 2)
    {
        throw DicomifierException("Missing frame number");
    }

    v8::Local<v8::Value> const arg = args[0];

    // Get PIXELDATA
    if (!arg->ToObject()->Has(v8::String::New("PIXELDATA")))
    {
        throw DicomifierException("Missing pixel data path");
    }
    v8::Local<v8::Array> pixeldata =
            arg->ToObject()->Get(v8::String::New("PIXELDATA")).As<v8::Array>();
    v8::String::Utf8Value utf8pixeldata(pixeldata->Get(0)->ToString());
    std::stringstream pixel_data;
    pixel_data << *utf8pixeldata;

    // Get VisuCoreWordType
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreWordType")))
    {
        throw DicomifierException(
                    "Missing mandatory Bruker field VisuCoreWordType");
    }
    v8::Local<v8::Array> wordtype =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreWordType")).As<v8::Array>();
    v8::String::Utf8Value utf8wordtype(wordtype->Get(0)->ToString());
    std::stringstream word_type;
    word_type << *utf8wordtype;

    // Get VisuCoreByteOrder
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreByteOrder")))
    {
        throw DicomifierException(
                    "Missing mandatory Bruker field VisuCoreByteOrder");
    }
    v8::Local<v8::Array> byteorder =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreByteOrder")).As<v8::Array>();
    v8::String::Utf8Value utf8byteorder(byteorder->Get(0)->ToString());
    std::stringstream byte_order;
    byte_order << *utf8byteorder;

    // Get VisuCoreSize
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreSize")))
    {
        throw DicomifierException(
                    "Missing mandatory Bruker field VisuCoreSize");
    }
    v8::Local<v8::Array> coresize =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreSize")).As<v8::Array>();
    int framesize = coresize->Get(0)->ToInt32()->Int32Value() *
                    coresize->Get(1)->ToInt32()->Int32Value();

    // Get the frame number
    v8::Local<v8::Value> const argindex = args[1];
    auto numberOfFrame = argindex->ToInt32()->Int32Value();

    if (args.Length() == 3)
    {
        // Get a flag to return all pixel data or a string for each frame
        v8::Local<v8::Value> const argflag = args[2];
        bool flag_all_data = argflag->ToBoolean()->BooleanValue();

        if (flag_all_data)
        {
            framesize *= numberOfFrame;
            numberOfFrame = 1;
        }
    }

    // Create the array to return
    v8::Local<v8::Array> array = v8::Array::New(numberOfFrame);

    // Convert each frame in base64 String
    bruker::pixel_data_converter converter;
    for (unsigned int i = 0; i < numberOfFrame; ++i)
    {
        // Read pixel data file and get the Frame i
        dcmtkpp::DataSet dataset;
        converter(framesize, i, pixel_data.str(), word_type.str(),
                  byte_order.str(), dataset);

        // Convert to JSON
        Json::Value const json_dset = dcmtkpp::as_json(dataset);

        // Store into the array
        array->Set(i, v8::String::New(
                       json_dset["7fe00010"]["InlineBinary"].asCString()));
    }

    return array;
}

v8::Handle<v8::Value> namespace_(v8::Arguments const & args)
{
    auto const path_js = args[0]->ToString();
    std::string path_utf8(path_js->Utf8Length(), '\0');
    path_js->WriteUtf8(&path_utf8[0]);

    v8::HandleScope scope;
    v8::Handle<v8::Object> ns = v8::Context::GetCurrent()->Global();

    std::istringstream stream(path_utf8);
    std::string item;

    while(std::getline(stream, item, '.'))
    {
        v8::Local<v8::String> item_js = v8::String::New(item.c_str());

        v8::Local<v8::Object> child;
        if(!ns->Has(item_js))
        {
            child = v8::Object::New();
            ns->Set(item_js, child);
        }
        else
        {
            child = ns->Get(item_js)->ToObject();
        }

        ns = child;
    }


    return scope.Close(ns);
}

/***********************************
 **********************************/

JavascriptVM
::JavascriptVM()
{
    // Create a new Isolate and make it the current one.
    this->_isolate = v8::Isolate::New();
    {

    /**********************************
     * Create all required structures *
     **********************************/

    //v8::Isolate::Scope isolate_scope(this->_isolate);
    v8::HandleScope handle_scope;

    auto global = v8::ObjectTemplate::New();

    // Create a new context.
    // Context must be ready before creating an array
    // cf. https://stackoverflow.com/questions/7015068/why-does-creating-new-v8array-before-v8scope-cause-segmentation-fault-but-v

    this->_context = v8::Context::New(NULL, global);
    v8::Context::Scope context_scope(this->_context);

    /**************************
     * Fill the global object *
     **************************/

#define DICOMIFIER_EXPOSE_FUNCTION(cpp_name, js_name) \
    this->_context->Global()->Set(\
        v8::String::New(js_name), \
        v8::FunctionTemplate::New(cpp_name)->GetFunction());

    DICOMIFIER_EXPOSE_FUNCTION(log, "log");
    DICOMIFIER_EXPOSE_FUNCTION(is_big_endian, "bigEndian");
    DICOMIFIER_EXPOSE_FUNCTION(load_pixel_data, "loadPixelData");
    DICOMIFIER_EXPOSE_FUNCTION(generate_uid, "dcmGenerateUniqueIdentifier");
    DICOMIFIER_EXPOSE_FUNCTION(namespace_, "namespace");

#undef DICOMIFIER_EXPOSE_FUNCTION

    auto myobject = v8::Object::New();
    myobject->Set(v8::String::New("inputs"), v8::Array::New());
    myobject->Set(v8::String::New("outputs"), v8::Array::New());

    this->_context->Global()->Set(
        v8::String::New("dicomifier"),
        myobject);
    }

    std::stringstream streamdictionary;
    streamdictionary << "dicomifier[\"dictionary\"] = "
                     << Dictionaries::get_instance().to_string() << ";";
    this->run(streamdictionary.str());

    std::string configuration_path("../configuration");
    char* value = getenv("DICOMIFIER_CONFIGURATION_DIR");
    if(value != NULL)
    {
        configuration_path = std::string(value);
    }

    std::stringstream functionfile;
    functionfile << configuration_path
                 << "/script_bruker2dicom/functions.js";
    std::stringstream frameindexgenerator;
    frameindexgenerator << configuration_path
                        << "/script_bruker2dicom/frameIndexGenerator.js";
}

JavascriptVM
::~JavascriptVM()
{
    this->_isolate->Dispose();
}

v8::Local<v8::Value>
JavascriptVM
::run(const std::string &script)
{
    // fix error: Cannot create a handle without a HandleScope
    v8::HandleScope handle_scope;
    v8::TryCatch trycatch;

    // Load the context
    v8::Context::Scope context_scope(this->_context);

    // Get the script
    auto source = v8::String::New(script.c_str());

    // Compile
    auto scriptJS = v8::Script::Compile(source);
    if(scriptJS.IsEmpty())
    {
        throw dicomifier::DicomifierException("Cannot compile JavaScript");
    }

    // Execute
    auto return_ = scriptJS->Run();
    if (return_.IsEmpty())
    {
        std::stringstream streamerror;
        streamerror << "JavaScript error: "
                    << *v8::String::AsciiValue(trycatch.Exception());
        throw DicomifierException(streamerror.str());
    }

    return return_;
}

v8::Local<v8::Value>
JavascriptVM
::run_file(std::string const & scriptpath)
{
    // Open file
    std::ifstream streamfile(scriptpath.c_str(), std::ifstream::binary);

    // Get file size
    streamfile.seekg(0, streamfile.end);
    auto const size = streamfile.tellg();
    streamfile.seekg(0, streamfile.beg);

    // Read file
    std::string buffer;
    buffer.resize(size);
    streamfile.read((char*)(&buffer[0]), size);

    // Close file
    streamfile.close();

    // Execute script
    return this->run(buffer);
}

} // namespace javascript

} // namespace dicomifier
