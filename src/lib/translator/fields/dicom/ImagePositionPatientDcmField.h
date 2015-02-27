/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dd00a025_9feb_4e1d_822d_9a07c849e345
#define _dd00a025_9feb_4e1d_822d_9a07c849e345

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The ImagePositionPatientDcmField class
 */
template<DcmEVR VR>
class ImagePositionPatientDcmField : public SubTag<VR>
{
public:
    typedef ImagePositionPatientDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ImagePositionPatientDcmField
    static Pointer New();
    
    /// Destroy the instance of ImagePositionPatientDcmField
    virtual ~ImagePositionPatientDcmField();
                     
    /**
     * @brief run: Convert Bruker ImagePositionPatientDcmField format into
     *             DICOM ImagePositionPatientDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of ImagePositionPatientDcmField
    ImagePositionPatientDcmField();

private:

};
    
} // namespace dicomifier

} // namespace translator

#include "ImagePositionPatientDcmField.txx"

#endif // _dd00a025_9feb_4e1d_822d_9a07c849e345
