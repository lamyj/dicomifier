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

namespace dicomifier
{
    
namespace factory
{
    
/**
 * @brief The SetElementCreator class: Factory for the class SetElement
 */
class SetElementCreator : public DicomCreatorBase
{
public:
    typedef SetElementCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SetElementCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of SetElementCreator
    virtual ~SetElementCreator();
    
    /**
     * @brief Create an object SetElement
     * @param value: XML node
     * @return new instancce of SetElement
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return SetElement
     */
    static std::string get_class_name() { return "SetElement"; }
    
protected:
    /// Create an instance of SetElementCreator
    SetElementCreator();
    
private:
    SetElementCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct ActionSetElementCreator
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
