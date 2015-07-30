/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

#include <boost/filesystem.hpp>

#include <dcmtkpp/json_converter.h>

#include "bruker/converters/pixel_data_converter.h"
#include "core/DicomifierException.h"
#include "core/Endian.h"
#include "dicom/Dictionaries.h"
#include "JavascriptVM.h"
#include "LoggerJS.h"
#include "core/Logger.h"

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

    v8::Local<v8::Value> const argindex = args[1];
    auto index = argindex->ToInt32()->Int32Value();

    bruker::converters::pixel_data_converter converter;
    dcmtkpp::DataSet dataset;
    converter(framesize, index, pixel_data.str(), word_type.str(),
              byte_order.str(), dataset);

    Json::Value json_dset = dcmtkpp::as_json(dataset);

    return v8::String::New(json_dset["7fe00010"]["InlineBinary"].asCString());
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

    context = v8::Context::New(NULL, global);
    v8::Context::Scope context_scope(context);

    /**************************
     * Fill the global object *
     **************************/

    context->Global()->Set(
        v8::String::New("log"),
        v8::FunctionTemplate::New(log)->GetFunction());

    context->Global()->Set(
        v8::String::New("bigEndian"),
        v8::FunctionTemplate::New(is_big_endian)->GetFunction());

    context->Global()->Set(
        v8::String::New("loadPixelData"),
        v8::FunctionTemplate::New(load_pixel_data)->GetFunction());

    context->Global()->Set(
        v8::String::New("dcmGenerateUniqueIdentifier"),
        v8::FunctionTemplate::New(generate_uid)->GetFunction());

    auto myobject = v8::Object::New();
    myobject->Set(v8::String::New("inputs"), v8::Array::New());
    myobject->Set(v8::String::New("outputs"), v8::Array::New());

    context->Global()->Set(
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

    // if file exist locally
    if (boost::filesystem::exists(boost::filesystem::path(functionfile.str())))
    {
        this->run_file(functionfile.str());
    }
    // else use default file
    else
    {
        this->run_file("/etc/dicomifier/script_bruker2dicom/functions.js");
    }

    // if file exist locally
    if (boost::filesystem::exists(
                boost::filesystem::path(frameindexgenerator.str())))
    {
        this->run_file(frameindexgenerator.str());
    }
    // else use default file
    else
    {
        this->run_file(
            "/etc/dicomifier/script_bruker2dicom/frameIndexGenerator.js");
    }
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
    v8::Context::Scope context_scope(context);

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
