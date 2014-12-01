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
    
class DicomSequenceField : public Tag
{
public:
    typedef DicomSequenceField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomSequenceField
    static Pointer New() { return Pointer(new Self()); }
    
    static Pointer New(dicomifier::TagAndRange const & tagrange, 
                       std::vector<Tag::Pointer> tags,
                       bool perframe)
        { return Pointer(new Self(tagrange, tags, perframe)); }
    
    virtual ~DicomSequenceField();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const { return ECT_DicomSequenceField; }
    
protected:
    DicomSequenceField();

    DicomSequenceField(dicomifier::TagAndRange const & tagrange, 
                       std::vector<Tag::Pointer> tags,
                       bool perframe);
    
private:
    std::vector<Tag::Pointer> _tags;
    
    TagAndRange _dicomtags;
    
    bool _perFrame;

};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _f758afe0_0cc2_4bb0_a657_c06982b2f5f1
