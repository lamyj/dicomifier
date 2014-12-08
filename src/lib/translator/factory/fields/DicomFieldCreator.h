/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1fc05880_7487_48d3_b15f_8609973a7de1
#define _1fc05880_7487_48d3_b15f_8609973a7de1

#include "translator/fields/DicomField.h"
#include "translator/fields/DicomSequenceField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The DicomFieldCreator class
 */
class DicomFieldCreator : public TranslationCreatorBase
{
public:
    typedef DicomFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of DicomFieldCreator
    virtual ~DicomFieldCreator();

    /**
     * @brief Create Pointer to class DicomField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new DicomField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return DicomField
     */
    static std::string get_class_name() { return "DicomField"; }

protected:
    /// Create an instance of DicomFieldCreator
    DicomFieldCreator();

private:
    DicomFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDicomFieldCreator
    {
        dicomifier::TagAndRange tagrange;
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        bool perframe;
        mutable dicomifier::translator::Tag::Pointer dicomfield;
        template<DcmEVR VR> void run() const;
    };
    
};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _1fc05880_7487_48d3_b15f_8609973a7de1
