/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c8fc62b0_9088_4b07_aefa_19555a8d4586
#define _c8fc62b0_9088_4b07_aefa_19555a8d4586

#include "factory/core/CreatorBase.h"

#include <boost/property_tree/ptree.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"

namespace dicomifier
{
    
namespace factory
{

template<typename T>
T 
CreatorBase
::_get(boost::property_tree::ptree const & tree, std::string const & path) const
{
    T value;
    try
    {
        value = tree.get<T>(path);
    }
    catch(boost::property_tree::ptree_bad_path const & e)
    {
        throw DicomifierException(e.what());
    }
    
    return value;
}

} // namespace factory

} // namespace dicomifier

#endif // _c8fc62b0_9088_4b07_aefa_19555a8d4586
