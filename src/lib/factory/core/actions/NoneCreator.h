/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9d102847_1c78_43d4_a92f_31595a2cbad2
#define _9d102847_1c78_43d4_a92f_31595a2cbad2

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class NoneCreator : public CreatorBase
{
public:
    typedef NoneCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~NoneCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) const;

    static std::string get_class_name() { return "None"; }

protected:
    NoneCreator();

private:
    NoneCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory

} // namespace dicomifier

#endif // _9d102847_1c78_43d4_a92f_31595a2cbad2
