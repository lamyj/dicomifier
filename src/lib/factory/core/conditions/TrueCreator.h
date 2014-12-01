/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8690cd8b_8e24_44f1_a3b2_b1715c563947
#define _8690cd8b_8e24_44f1_a3b2_b1715c563947

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{

class TrueCreator : public CreatorBase
{
public:
    typedef TrueCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~TrueCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "True"; }

protected:
    TrueCreator();

private:
    TrueCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _8690cd8b_8e24_44f1_a3b2_b1715c563947
