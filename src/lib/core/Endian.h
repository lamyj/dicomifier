/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _495bd214_52fe_454c_a5a4_7c725e27bde2
#define _495bd214_52fe_454c_a5a4_7c725e27bde2

namespace dicomifier
{

namespace endian
{

/**
 * @brief is_big_endian: check host Endianness
 * @return true if host is in big Endian, false otherwise
 */
static bool is_big_endian()
{
    union
    {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return (bint.c[0] == 1);
}

/**
 * @brief is_little_endian: check host Endianness
 * @return true if host is in little Endian, false otherwise
 */
static bool is_little_endian()
{
    return !is_big_endian();
}

/**
 * @brief swap: Convert Little Endian to Big Endian or Big Endian to Little Endian
 * @param objecttoswap: object to convert
 * @param size: size of the object
 */
static void swap(char* objecttoswap, int const & size)
{
    for (unsigned int i = 0; i < size/2; i++)
    {
        char temp;
        memcpy(&temp, objecttoswap+i, 1);
        memcpy(objecttoswap+i, objecttoswap+size-(i+1), 1);
        memcpy(objecttoswap+size-(i+1), &temp, 1);
    }
}

/**
 * @brief swap_letoh: Convert Little Endian to host Endianness
 * @param objecttoswap: object to convert
 * @param size: size of the object
 */
static void swap_letoh(char * objecttoswap, int const & size)
{
    if (is_little_endian())
    {// Nothing to do: already in Little Endian
        return;
    }

    // Swap to Big Endian
    swap(objecttoswap, size);
}

/**
 * @brief swap_betoh: Convert Big Endian to host Endianness
 * @param objecttoswap: object to convert
 * @param size: size of the object
 */
static void swap_betoh(char * objecttoswap, int const & size)
{
    if (is_big_endian())
    {// Nothing to do: already in Big Endian
        return;
    }

    // Swap to Little Endian
    swap(objecttoswap, size);
}

} // namespace endian

} // namespace dicomifier

#endif // _495bd214_52fe_454c_a5a4_7c725e27bde2
