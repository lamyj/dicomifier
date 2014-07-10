/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1a0476fd_40cd_4fea_81b3_de1bc5b400ba
#define _1a0476fd_40cd_4fea_81b3_de1bc5b400ba

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{

class FalseCreator : public CreatorBase
{
public:
    typedef FalseCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~FalseCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "False"; }

protected:
    FalseCreator();

private:
    FalseCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _1a0476fd_40cd_4fea_81b3_de1bc5b400ba

