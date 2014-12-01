/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6ba82a85_c5d4_4189_a467_b1acecf9722c
#define _6ba82a85_c5d4_4189_a467_b1acecf9722c

#include "translator/fields/dicom/StackIDDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class StackIDDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef StackIDDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~StackIDDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "StackIDDcmField"; }
    
protected:
    StackIDDcmFieldCreator();

private:
    StackIDDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorStackIDDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer stackid;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _6ba82a85_c5d4_4189_a467_b1acecf9722c
