/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d93058ed_d134_4683_823f_7c6f7c27a7b4
#define _d93058ed_d134_4683_823f_7c6f7c27a7b4

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class AnyCreator : public CreatorBase
{
public:
    typedef AnyCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~AnyCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "Any"; }

protected:
    AnyCreator();

private:
    AnyCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _d93058ed_d134_4683_823f_7c6f7c27a7b4
