/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b07764f2_55d7_4b6a_970e_ee741b69f1b0
#define _b07764f2_55d7_4b6a_970e_ee741b69f1b0

#include "factory/dicom/DicomCreatorBase.h"

namespace dicomifier
{

namespace factory
{
    
/**
 * @brief The ElementMatchCreator class: Factory for the class ElementMatch
 */
class ElementMatchCreator : public DicomCreatorBase
{
public:
    typedef ElementMatchCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ElementMatchCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of ElementMatchCreator
    virtual ~ElementMatchCreator();
    
    /**
     * @brief Create an object ElementMatch
     * @param value: XML node
     * @return new instancce of ElementMatch
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return ElementMatch
     */
    static std::string get_class_name() { return "ElementMatch"; }

protected:
    /// Create an instance of ElementMatchCreator
    ElementMatchCreator();

private:
    ElementMatchCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct ActionElementMatchCreator
    {
        DcmItem* dataset;
        std::vector<TagAndRange> tags;
        std::string value;
        mutable dicomifier::Object::Pointer matchElement;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _b07764f2_55d7_4b6a_970e_ee741b69f1b0
