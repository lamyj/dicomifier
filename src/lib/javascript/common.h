/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e8ffa1b0_70a9_41b9_a2f7_028ab339a707
#define _e8ffa1b0_70a9_41b9_a2f7_028ab339a707

#include <vector>

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/// @brief Return the C++ object stored in the V8 value.
template<typename T>
T as_scalar(v8::Local<v8::Value> const & value);

/// @brief Return the C++ object stored in the property of the V8 object.
template<typename T>
T as_scalar(
    v8::Local<v8::Value> const & value, v8::Local<v8::String> const & name);

/// @brief Return the C++ object stored in the property of the V8 object.
template<typename T>
T as_scalar(v8::Local<v8::Value> const & value, char const * name);

/// @brief Return the C++ object stored in the i-th position of the V8 array.
template<typename T>
T as_scalar(
    v8::Local<v8::Object> const & object, v8::Local<v8::String> const & name,
    unsigned int index);

/// @brief Return the C++ object stored in the i-th position of the V8 array.
template<typename T>
T as_scalar(
    v8::Local<v8::Object> const & object, char const * name,
    unsigned int index);

/// @brief Return a vector of C++ object stored in the property of the V8 object.
template<typename T>
std::vector<T>
as_vector(
    v8::Local<v8::Object> const & object, v8::Local<v8::String> const & name);

/// @brief Return a vector of C++ object stored in the property of the V8 object.
template<typename T>
std::vector<T>
as_vector(v8::Local<v8::Object> const & object, char const * name);

v8::Handle<v8::Value> namespace_(v8::Arguments const & args);

v8::Handle<v8::Value> require(v8::Arguments const & args);

v8::Handle<v8::Value> is_big_endian(v8::Arguments const &);

}

}

#include "javascript/common.txx"

#endif // _e8ffa1b0_70a9_41b9_a2f7_028ab339a707

