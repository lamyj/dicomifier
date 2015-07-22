/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "JavascriptVM.h"
#include "LoggerJS.h"

namespace dicomifier
{

namespace javascript
{

JavascriptVM
::JavascriptVM()
{
    // Initialize V8.
    v8::V8::Initialize();

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
        v8::String::New("inputs"),
        v8::Array::New());

    context->Global()->Set(
        v8::String::New("outputs"),
        v8::Array::New());
    }
}

JavascriptVM
::~JavascriptVM()
{
    this->_isolate->Dispose();

    v8::V8::Dispose();
}

v8::Local<v8::Value>
JavascriptVM
::run(const std::string &script)
{
    // fix error: Cannot create a handle without a HandleScope
    v8::HandleScope handle_scope;

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
    return scriptJS->Run();
}

} // namespace javascript

} // namespace dicomifier
