/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <stdint.h>

namespace dicomifier
{

namespace endian
{

/**
 * @brief Test if the current byte order is big endian.
 */
bool is_big_endian()
{
    union Endianness
    {
        uint16_t i;
        char c[2];
    };
    Endianness endianness;
    endianness.i = 0x0102;

    return (endianness.c[0] == 1);
}

/**
 * @brief Test if the current byte order is little endian.
 */
bool is_little_endian()
{
    return !is_big_endian();
}

} // namespace endian

} // namespace dicomifier

