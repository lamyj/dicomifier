/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _26ab5a53_b1ad_4511_b73a_17e54bb74b19
#define _26ab5a53_b1ad_4511_b73a_17e54bb74b19

#include <cstring>
#include <stdint.h>
#include <string>

namespace dicomifier
{

namespace hashcode
{

/**
 * Return hashcode for a given iterator
 * @param begin: iterator's begin
 * @param end: iterator's end
 * @return hashcode
 */
template<typename TIterator>
uint32_t hashCode(TIterator begin, TIterator end)
{
    uint32_t hash=0;
    TIterator it(begin);
    while(it != end)
    {
        hash = 31*hash+(*it);
        ++it;
    }
    return hash;
}

/**
 * Return hashcode for a given string
 * @param s: string value
 * @return hashcode
 */
template<typename TString>
uint32_t hashCode(TString const & s)
{
    char const * const begin = s.c_str();
    char const * const end = begin+s.size();
    return dicomifier::hashcode::hashCode(begin, end);
}

/**
 * Convert hashcode to string value
 * @param hash: hashcode
 * @return corresponding string
 */
std::string hashToString(uint32_t hash)
{
    const size_t bufferSize = 9; // Use one more char for '\0'
    char temp[bufferSize];
    memset(&temp[0], 0, bufferSize); // Set all to '\0'
    snprintf(&temp[0], bufferSize, "%08X", hash);
    memset(&temp[bufferSize-1], 0, 1); // make sure last char is '\0'
    return std::string(temp);
}

} // namespace hashcode

} // namespace dicomifier

#endif // _26ab5a53_b1ad_4511_b73a_17e54bb74b19
