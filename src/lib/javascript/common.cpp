/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/common.h"

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <v8.h>

#include "core/DicomifierException.h"
#include "core/Endian.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace javascript
{

template<>
bool as_scalar(v8::Local<v8::Value> const & value)
{
    auto const scalar = value->ToBoolean();
    if(scalar.IsEmpty())
    {
        throw DicomifierException("Item is not a boolean");
    }
    return scalar->BooleanValue();
}

template<>
double as_scalar(v8::Local<v8::Value> const & value)
{
    auto const scalar = value->ToNumber();
    if(scalar.IsEmpty())
    {
        throw DicomifierException("Item is not a number");
    }
    return scalar->Value();
}

template<>
std::string as_scalar(v8::Local<v8::Value> const & value)
{
    auto const scalar = value->ToString();
    if(scalar.IsEmpty())
    {
        throw DicomifierException("Item is not a string");
    }
    return *v8::String::Utf8Value(scalar);
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

v8::Handle<v8::Value> require(v8::Arguments const & args)
{
    auto const path_js = args[0]->ToString();
    std::string path_utf8(path_js->Utf8Length(), '\0');
    path_js->WriteUtf8(&path_utf8[0]);

    boost::filesystem::path absolute_path;
    // 1. The directory containing the current file
    if(boost::filesystem::is_regular(boost::filesystem::current_path()/path_utf8))
    {
        absolute_path = boost::filesystem::current_path()/path_utf8;
    }
    // 2. The paths listed in DICOMIFIER_JS_PATH (environment variable)
    else if(absolute_path.empty() && getenv("DICOMIFIER_JS_PATH") != NULL)
    {
        boost::filesystem::path const root(getenv("DICOMIFIER_JS_PATH"));
        if(boost::filesystem::is_regular(root/path_utf8))
        {
            absolute_path = root/path_utf8;
        }
    }
    // 3. The path listed in DICOMIFIER_DEFAULT_JS_PATH (compiler symbol)
#ifdef DICOMIFIER_DEFAULT_JS_PATH
    else if(absolute_path.empty())
    {
        boost::filesystem::path const root(DICOMIFIER_DEFAULT_JS_PATH);
        if(boost::filesystem::is_regular(root/path_utf8))
        {
            absolute_path = root/path_utf8;
        }
    }
#else
#warning "No default Javascript path"
#endif

    if(absolute_path.empty())
    {
        return v8::ThrowException(
                    v8::String::New(("No such file: "+path_utf8).c_str()));
    }

    auto const context = v8::Context::GetCurrent();
    return JavascriptVM::run_file(absolute_path.generic_string(), context);
}

v8::Handle<v8::Value> is_big_endian(v8::Arguments const &)
{
    return v8::Boolean::New(::dicomifier::is_big_endian());
}

}

}
