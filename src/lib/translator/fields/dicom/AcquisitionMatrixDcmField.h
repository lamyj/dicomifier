/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f9b4ab71_c803_41c6_aeec_9e1db1683147
#define _f9b4ab71_c803_41c6_aeec_9e1db1683147

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class AcquisitionMatrixDcmField : public SubTag<VR>
{
public:
    typedef AcquisitionMatrixDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of AcquisitionMatrixDcmField
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of AcquisitionMatrixDcmField
     * @param tag: Bruker field to process
     * @return new instance of AcquisitionMatrixDcmField
     */
    static Pointer New(Tag::Pointer tag);
    
    /// Destroy the instance of AcquisitionMatrixDcmField
    virtual ~AcquisitionMatrixDcmField();
                     
    /**
     * @brief run: Convert Bruker AcquisitionMatrixDcmField format into
     *             DICOM AcquisitionMatrixDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_AcquisitionMatrixDcmField
     */
    virtual ClassType get_class_type() const 
            { return ECT_AcquisitionMatrixDcmField; }

protected:
    /// Create an instance of AcquisitionMatrixDcmField
    AcquisitionMatrixDcmField();
    
    /**
     * @brief Create an instance of AcquisitionMatrixDcmField
     * @param tag: Bruker field to process
     */
    AcquisitionMatrixDcmField(Tag::Pointer tag);

private:
    /// Bruker field to process
    Tag::Pointer _tag;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "AcquisitionMatrixDcmField.txx"

#endif // _f9b4ab71_c803_41c6_aeec_9e1db1683147
