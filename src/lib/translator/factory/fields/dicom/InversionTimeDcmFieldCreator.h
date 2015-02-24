/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _78d13e11_e213_49ed_9be5_0655332c43ed
#define _78d13e11_e213_49ed_9be5_0655332c43ed

#include "translator/fields/dicom/InversionTimeDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The InversionTimeDcmFieldCreator class
 */
class InversionTimeDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef InversionTimeDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InversionTimeDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of InversionTimeDcmFieldCreator
    virtual ~InversionTimeDcmFieldCreator();

    /**
     * @brief Create Pointer to class InversionTimeDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new InversionTimeDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return InversionTimeDcmField
     */
    static std::string get_class_name() { return "InversionTimeDcmField"; }

protected:
    /// Create an instance of InversionTimeDcmFieldCreator
    InversionTimeDcmFieldCreator();

private:
    InversionTimeDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorInversionTimeDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer inversiontime;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _78d13e11_e213_49ed_9be5_0655332c43ed
