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
    
class InversionTimeDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef InversionTimeDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~InversionTimeDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "InversionTimeDcmField"; }

protected:
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
