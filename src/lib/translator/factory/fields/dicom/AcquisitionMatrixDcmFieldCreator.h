/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6b049fcf_6d34_4d71_af4d_071ce084bde5
#define _6b049fcf_6d34_4d71_af4d_071ce084bde5

#include "translator/fields/dicom/AcquisitionMatrixDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class AcquisitionMatrixDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef AcquisitionMatrixDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~AcquisitionMatrixDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "AcquisitionMatrixDcmField"; }

protected:
    AcquisitionMatrixDcmFieldCreator();

private:
    AcquisitionMatrixDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorAcquisitionMatrixDcmFieldCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer acquisitionmatrix;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _6b049fcf_6d34_4d71_af4d_071ce084bde5
