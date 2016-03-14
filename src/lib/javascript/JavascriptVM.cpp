/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/JavascriptVM.h"

#include <fstream>
#include <sstream>
#include <string>

#include <odil/registry.h>
#include <v8.h>

#include "javascript/bruker.h"
#include "javascript/common.h"
#include "javascript/dicom.h"
#include "javascript/LoggerJS.h"
#include "javascript/nifti.h"

namespace dicomifier
{

namespace javascript
{

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
    DICOMIFIER_EXPOSE_FUNCTION(convertPixelDataToDicom, "convertPixelDataToDicom");
    DICOMIFIER_EXPOSE_FUNCTION(generate_dicom_filename, "generateDICOMFileName");
    DICOMIFIER_EXPOSE_FUNCTION(read_bruker_directory, "readBrukerDirectory");
    DICOMIFIER_EXPOSE_FUNCTION(read_dicom, "readDICOM");
    DICOMIFIER_EXPOSE_FUNCTION(write_nifti, "writeNIfTI");
    DICOMIFIER_EXPOSE_FUNCTION(write_dicom, "writeDICOM");
    DICOMIFIER_EXPOSE_FUNCTION(generate_uid, "dcmGenerateUniqueIdentifier");
    DICOMIFIER_EXPOSE_FUNCTION(require, "require");
    DICOMIFIER_EXPOSE_FUNCTION(namespace_, "namespace");
    DICOMIFIER_EXPOSE_FUNCTION(getTagKeyword, "getTagKeyword");

#undef DICOMIFIER_EXPOSE_FUNCTION

    auto myobject = v8::Object::New();
    myobject->Set(v8::String::New("inputs"), v8::Array::New());
    myobject->Set(v8::String::New("outputs"), v8::Array::New());

    this->_context->Global()->Set(
        v8::String::New("dicomifier"),
        myobject);
    }

    std::stringstream dictionary_as_json;
    {
        dictionary_as_json << "{";

        bool first = true;
        for(auto it = odil::registry::public_dictionary.begin();
            it != odil::registry::public_dictionary.end(); ++it)
        {
            if(it->first.get_type() != odil::ElementsDictionaryKey::Type::Tag)
            {
                continue;
            }

            if (!first)
            {
                dictionary_as_json << ",";
            }
            first = false;

            dictionary_as_json
                << "\"" << it->second.keyword
                << "\": [\"" << it->second.vr
                << "\",\"" << std::string(it->first.get_tag()) << "\"]";
        }

        dictionary_as_json << "}";
    }

    std::stringstream streamdictionary;
    streamdictionary << "dicomifier[\"dictionary\"] = "
                     << dictionary_as_json.str()
                     << ";";
    JavascriptVM::run(streamdictionary.str(), this->get_context());
}

JavascriptVM
::~JavascriptVM()
{
    this->_isolate->Dispose();
}

v8::Handle<v8::Context>
JavascriptVM
::get_context() const
{
    return this->_context;
}

v8::Local<v8::Value>
JavascriptVM
::run(std::string const & source, v8::Handle<v8::Context> const & context)
{
    v8::Context::Scope context_scope(context);

    v8::HandleScope handle_scope;
    v8::TryCatch try_catch;

    auto const source_js = v8::String::New(source.c_str());
    auto const script = v8::Script::Compile(source_js);
    if(script.IsEmpty())
    {
        std::ostringstream message;
        message << "Line " << try_catch.Message()->GetLineNumber() << ": "
            << *v8::String::AsciiValue(try_catch.Exception());
        throw dicomifier::DicomifierException(message.str());
    }

    auto const result = script->Run();
    if(result.IsEmpty())
    {
        std::ostringstream message;
        message << "Line " << try_catch.Message()->GetLineNumber() << ": "
            << *v8::String::AsciiValue(try_catch.Exception());
        throw dicomifier::DicomifierException(message.str());
    }

    return result;
}

v8::Local<v8::Value>
JavascriptVM
::run_file(std::string const & scriptpath, v8::Handle<v8::Context> const & context)
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
    return JavascriptVM::run(buffer, context);
}

} // namespace javascript

} // namespace dicomifier
