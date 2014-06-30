/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _af7ae5f1_969d_404d_be7a_4cfe95455eac
#define _af7ae5f1_969d_404d_be7a_4cfe95455eac

#include <memory>

#include <boost/property_tree/ptree.hpp>

#include "core/Object.h"

namespace dicomifier
{
    
namespace factory
{
    
class CreatorBase
{
public:
    typedef CreatorBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    virtual ~CreatorBase();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) const = 0;

protected:
    CreatorBase();

private:
    CreatorBase(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory

} // namespace dicomifier

#endif // _af7ae5f1_969d_404d_be7a_4cfe95455eac
