/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7a6fdce5_5d17_49f0_8604_2e37b96d427d
#define _7a6fdce5_5d17_49f0_8604_2e37b96d427d

#include "factory/dicom/DicomCreatorBase.h"
#include "dicom/ElementTraits.h"
#include "dicom/TagAndRange.h"

namespace dicomifier
{
    
namespace factory
{
    
class SetElementCreator : public DicomCreatorBase
{
public:
    typedef SetElementCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~SetElementCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "SetElement"; }
    
protected:
    SetElementCreator();
    
private:
    SetElementCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct CreateSetElement
    {
        DcmItem* dataset;
        std::vector<TagAndRange> tags;
        std::string value;
        mutable dicomifier::Object::Pointer setElement;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory
    
} // namespace dicomifier

#endif // _7a6fdce5_5d17_49f0_8604_2e37b96d427d
