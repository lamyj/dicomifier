/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f758afe0_0cc2_4bb0_a657_c06982b2f5f1
#define _f758afe0_0cc2_4bb0_a657_c06982b2f5f1

#include "dicom/TagAndRange.h"
#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
/**
 * @brief The DicomSequenceField class: Create Sequence with Bruker field
 */
class DicomSequenceField : public Tag
{
public:
    typedef DicomSequenceField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomSequenceField
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * @brief Create pointer to new instance of DicomSequenceField
     * @param tagrange: Tag of the sequence
     * @param tags: Tag contained by the sequence
     * @param perframe: flag indicate if sequence contains 1 item for each frame
     * @return new instance of DicomSequenceField
     */
    static Pointer New(dicomifier::TagAndRange const & tagrange, 
                       std::vector<Tag::Pointer> tags,
                       bool perframe)
        { return Pointer(new Self(tagrange, tags, perframe)); }
    
    /// Destroy the instance of DicomSequenceField
    virtual ~DicomSequenceField();
    
    /**
     * @brief run: Create DICOM sequence
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_DicomSequenceField
     */
    virtual ClassType get_class_type() const { return ECT_DicomSequenceField; }
    
protected:
    /// Create an instance of DicomSequenceField
    DicomSequenceField();

    /**
     * @brief Create an instance of DicomSequenceField
     * @param tagrange: Tag of the sequence
     * @param tags: Tag contained by the sequence
     * @param perframe: flag indicate if sequence contains 1 item for each frame
     */
    DicomSequenceField(dicomifier::TagAndRange const & tagrange, 
                       std::vector<Tag::Pointer> tags,
                       bool perframe);
    
private:
    /// Tags in the sequence
    std::vector<Tag::Pointer> _tags;
    
    /// Tag of the sequence
    TagAndRange _dicomtags;
    
    /// flag indicate if sequence contains 1 item for each frame
    bool _perFrame;

};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _f758afe0_0cc2_4bb0_a657_c06982b2f5f1
