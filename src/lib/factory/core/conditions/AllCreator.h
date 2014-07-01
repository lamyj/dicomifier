/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b1d06209_27d4_42e6_a1d6_26b8fe3bd4a8
#define _b1d06209_27d4_42e6_a1d6_26b8fe3bd4a8

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class AllCreator : public CreatorBase
{
public:
    typedef AllCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~AllCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) const;

    static std::string get_class_name() { return "All"; }

protected:
    AllCreator();

private:
    AllCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _b1d06209_27d4_42e6_a1d6_26b8fe3bd4a8
