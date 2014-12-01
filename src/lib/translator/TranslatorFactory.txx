/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _51716d45_ca4d_4679_b826_2120758c8917
#define _51716d45_ca4d_4679_b826_2120758c8917

#include "TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
template<typename T>
unsigned int
TranslatorFactory
::register_()
{
    this->_creators.insert(std::make_pair(
        T::get_class_name(), [] () { return T::New(); }));
    return this->_creators.size();
}
    
} // namespace translator

} // namespace dicomifier

#endif // _51716d45_ca4d_4679_b826_2120758c8917
