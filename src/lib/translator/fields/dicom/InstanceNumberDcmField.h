/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _46b33bf9_e5ae_40ad_b5f3_0374d1867aec
#define _46b33bf9_e5ae_40ad_b5f3_0374d1867aec

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The InstanceNumberDcmField class
 */
template<DcmEVR VR>
class InstanceNumberDcmField : public SubTag<VR>
{
public:
    typedef InstanceNumberDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InstanceNumberDcmField
    static Pointer New();
    
    /// Destroy the instance of InstanceNumberDcmField
    virtual ~InstanceNumberDcmField();
                     
    /**
     * @brief run: Compute instance number with Generator
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_InstanceNumberDcmField
     */
    virtual ClassType get_class_type() const 
            { return ECT_InstanceNumberDcmField; }
    
protected:
    /// Create an instance of InstanceNumberDcmField
    InstanceNumberDcmField();

private:

};
    
} // namespace translator
   
} // namespace dicomifier

#include "InstanceNumberDcmField.txx"

#endif // _46b33bf9_e5ae_40ad_b5f3_0374d1867aec
