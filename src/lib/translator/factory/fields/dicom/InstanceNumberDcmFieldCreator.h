/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2f5ebdfe_45ef_49e8_91c7_39cf8a0dbb8b
#define _2f5ebdfe_45ef_49e8_91c7_39cf8a0dbb8b

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The InstanceNumberDcmFieldCreator class
 */
class InstanceNumberDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef InstanceNumberDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InstanceNumberDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of InstanceNumberDcmFieldCreator
    virtual ~InstanceNumberDcmFieldCreator();

    /**
     * @brief Create Pointer to class InstanceNumberDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new InstanceNumberDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return InstanceNumberDcmField
     */
    static std::string get_class_name() { return "InstanceNumberDcmField"; }

protected:
    /// Create an instance of InstanceNumberDcmFieldCreator
    InstanceNumberDcmFieldCreator();

private:
    InstanceNumberDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorInstanceNumberDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer instancenumber;
        template<DcmEVR VR> void run() const;
    };
    
};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _2f5ebdfe_45ef_49e8_91c7_39cf8a0dbb8b
