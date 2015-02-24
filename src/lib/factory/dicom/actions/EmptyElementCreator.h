/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d620edec_8f58_4338_94bd_0b5d1a7fdeb8
#define _d620edec_8f58_4338_94bd_0b5d1a7fdeb8

#include "factory/dicom/DicomCreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
/**
 * @brief The EmptyElementCreator class: Factory for the class EmptyElement
 */
class EmptyElementCreator : public DicomCreatorBase
{
public:
    typedef EmptyElementCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of EmptyElementCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of EmptyElementCreator
    virtual ~EmptyElementCreator();
    
    /**
     * @brief Create an object EmptyElement
     * @param value: XML node
     * @return new instancce of EmptyElement
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return EmptyElement
     */
    static std::string get_class_name() { return "EmptyElement"; }

protected:
    /// Create an instance of EmptyElementCreator
    EmptyElementCreator();

private:
    EmptyElementCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _d620edec_8f58_4338_94bd_0b5d1a7fdeb8
