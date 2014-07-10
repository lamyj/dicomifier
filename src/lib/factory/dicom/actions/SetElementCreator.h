/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7a6fdce5_5d17_49f0_8604_2e37b96d427d
#define _7a6fdce5_5d17_49f0_8604_2e37b96d427d

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class SetElementCreator : public CreatorBase
{
public:
    typedef SetElementCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~SetElementCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "SetElement"; }
    
    template<DcmEVR VR>
    Object::Pointer Create(DcmDataset* dataset, DcmTag const & tag, 
                           std::string const & value) const;
    
protected:
    SetElementCreator();
    
private:
    SetElementCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace factory
    
} // namespace dicomifier

#endif // _7a6fdce5_5d17_49f0_8604_2e37b96d427d
