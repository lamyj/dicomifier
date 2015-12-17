/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _868b4bf6_4047_489a_83f3_729445de7feb
#define _868b4bf6_4047_489a_83f3_729445de7feb

#include "javascript/common.h"

#include <vector>

#include <v8.h>

#include "core/DicomifierException.h"

namespace dicomifier
{

namespace javascript
{

template<typename T>
std::vector<T>
as_vector(
    v8::Local<v8::Object> const & object, v8::Local<v8::String> const & name)
{
    if(!object->Has(name))
    {
        throw DicomifierException("No such property");
    }

    auto const array = object->Get(name).As<v8::Array>();
    if(array.IsEmpty())
    {
        throw DicomifierException("Property is not a array");
    }

    std::vector<T> result(array->Length());
    for(int32_t i=0; i<array->Length(); ++i)
    {
        auto const item = array->Get(i);
        result[i] = as_scalar<T>(item);
    }

    return result;
}

template<typename T>
std::vector<T>
as_vector(v8::Local<v8::Object> const & object, char const * name)
{
    return as_vector<T>(object, v8::String::New(name));
}

template<typename T>
T as_scalar(
    v8::Local<v8::Object> const & object, v8::Local<v8::String> const & name,
    int index)
{
    if(!object->Has(name))
    {
        throw DicomifierException("No such property");
    }

    auto const array = object->Get(name).As<v8::Array>();
    if(array.IsEmpty())
    {
        throw DicomifierException("Property is not a array");
    }

    auto const item = array->Get(index);
    if(item.IsEmpty())
    {
        throw DicomifierException("No such item");
    }

    return as_scalar<T>(item);
}

template<typename T>
T
as_scalar(v8::Local<v8::Object> const & object, char const * name, int index)
{
    return as_scalar<T>(object, v8::String::New(name), index);
}

template<typename T>
T as_scalar(
    v8::Local<v8::Object> const & object, v8::Local<v8::String> const & name)
{
    if(!object->Has(name))
    {
        throw DicomifierException("No such property");
    }

    auto const scalar = object->Get(name);
    return as_scalar<T>(scalar);
}

template<typename T>
T
as_scalar(v8::Local<v8::Object> const & object, char const * name)
{
    return as_scalar<T>(object, v8::String::New(name));
}

}

}

#endif // _868b4bf6_4047_489a_83f3_729445de7feb

