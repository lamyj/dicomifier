/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d86e03aa_6c3f_4233_b4ff_54c9d6fffc91
#define _d86e03aa_6c3f_4233_b4ff_54c9d6fffc91

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The ConstantFieldCreator class
 */
class ConstantFieldCreator : public TranslationCreatorBase
{
public:
    typedef ConstantFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ConstantFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of ConstantFieldCreator
    virtual ~ConstantFieldCreator();

    /**
     * @brief Create Pointer to class ConstantField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new ConstantField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return ConstantField
     */
    static std::string get_class_name() { return "ConstantField"; }

protected:
    /// Create an instance of ConstantFieldCreator
    ConstantFieldCreator();

private:
    ConstantFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorConstantFieldCreator
    {
        std::string value;
        mutable dicomifier::translator::Tag::Pointer constantField;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _d86e03aa_6c3f_4233_b4ff_54c9d6fffc91
