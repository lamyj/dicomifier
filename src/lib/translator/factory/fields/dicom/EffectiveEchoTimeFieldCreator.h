/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2504859e_84ff_41ce_b3bb_2f175bc11732
#define _2504859e_84ff_41ce_b3bb_2f175bc11732

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

/**
 * @brief The EffectiveEchoTimeFieldCreator class
 */
class EffectiveEchoTimeFieldCreator : public TranslationCreatorBase
{
public:
    typedef EffectiveEchoTimeFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of EffectiveEchoTimeFieldCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of EffectiveEchoTimeFieldCreator
    virtual ~EffectiveEchoTimeFieldCreator();

    /**
     * @brief Create Pointer to class EffectiveEchoTimeField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new EffectiveEchoTimeField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return EffectiveEchoTimeField
     */
    static std::string get_class_name() { return "EffectiveEchoTimeField"; }

protected:
    /// Create an instance of EffectiveEchoTimeFieldCreator
    EffectiveEchoTimeFieldCreator();

private:
    EffectiveEchoTimeFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorEffectiveEchoTimeFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer effectiveechotime;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _2504859e_84ff_41ce_b3bb_2f175bc11732
