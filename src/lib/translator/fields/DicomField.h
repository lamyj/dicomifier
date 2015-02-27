/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _42438b70_01c5_4513_b92d_1ea64bd22ef2
#define _42438b70_01c5_4513_b92d_1ea64bd22ef2

#include "dicom/TagAndRange.h"
#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The DicomField class
 */
template<DcmEVR VR>
class DicomField : public Tag
{
public:
    typedef DicomField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    
    /// Create pointer to new instance of DicomField
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of DicomField
     * @param tagrange: DICOM tag key
     * @param tag: Value to set for this DICOM tag
     * @return new instance of DicomField
     */
    static Pointer New(dicomifier::TagAndRange const & tagrange, 
                       Tag::Pointer tag);
    
    /// Destroy the instance of DicomField
    virtual ~DicomField();
    
    /**
     * @brief run: Compute field values and insert into DICOM Dataset
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:

private:
    /// Create an instance of DicomField
    DicomField();

    /**
     * @brief Create an instance of DicomField
     * @param tagrange: DICOM tag key
     * @param tag: Value to set for this DICOM tag
     */
    DicomField(dicomifier::TagAndRange const & tagrange, Tag::Pointer tag);
    
    /// DICOM tag key
    TagAndRange _dicomtags;
    
    /// Value to set for this DICOM tag
    Tag::Pointer _tag;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#include "DicomField.txx"

#endif // _42438b70_01c5_4513_b92d_1ea64bd22ef2
