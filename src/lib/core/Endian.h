/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _495bd214_52fe_454c_a5a4_7c725e27bde2
#define _495bd214_52fe_454c_a5a4_7c725e27bde2

#include <stdint.h>

namespace dicomifier
{

namespace endian
{

/**
 * @brief Test if the current byte order is big endian.
 */
bool is_big_endian();

/**
 * @brief Test if the current byte order is little endian.
 */
bool is_little_endian();

/**
 * @brief Swap the endianness of given object in place.
 *
 * The object must be a primitive data type.
 */
template<typename T>
void swap(T & object)
{
    char * buffer = reinterpret_cast<char*>(&object);
    for (unsigned int i = 0; i < sizeof(object)/2; ++i)
    {
        char const temp = buffer[i];
        buffer[i] = buffer[sizeof(object)-i-1];
        buffer[sizeof(object)-i-1] = temp;
    }
}

/**
 * @brief Swap the endianness of the given sequence in place.
 *
 * The sequence must contain primitive data types.
 */
template<typename TIterator>
void swap(TIterator begin, TIterator end)
{
    for(TIterator it=begin; it!=end; ++it)
    {
        swap(*it);
    }
}

/**
 * @brief Adapt the endianness of big-endian object to the current byte order.
 *
 * The object must be a primitive data type.
 */
template<typename T>
void from_big_endian(T & object)
{
    if(is_little_endian())
    {
        swap(object);
    }
}

/**
 * @brief Adapt the endianness of little-endian object to the current byte order.
 *
 * The object must be a primitive data type.
 */
template<typename T>
void from_little_endian(T & object)
{
    if(is_big_endian())
    {
        swap(object);
    }
}

/**
 * @brief Adapt the endianness of big-endian sequence to the current byte order.
 *
 * The sequence must contain primitive data types.
 */
template<typename TIterator>
void from_big_endian(TIterator begin, TIterator end)
{
    if(is_little_endian())
    {
        dicomifier::endian::swap(begin, end);
    }
}

/**
 * @brief Adapt the endianness of little-endian sequence to the current byte order.
 *
 * The sequence must contain primitive data types.
 */
template<typename TIterator>
void from_little_endian(TIterator begin, TIterator end)
{
    if(is_big_endian())
    {
        dicomifier::endian::swap(begin, end);
    }
}

} // namespace endian

} // namespace dicomifier

#endif // _495bd214_52fe_454c_a5a4_7c725e27bde2
