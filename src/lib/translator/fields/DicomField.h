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
    
    static Pointer New(dicomifier::TagAndRange const & tagrange, 
                       Tag::Pointer tag);
    
    virtual ~DicomField();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const { return ECT_DicomField; }
    
protected:

private:
    DicomField();
    DicomField(dicomifier::TagAndRange const & tagrange, Tag::Pointer tag);
    
    TagAndRange _dicomtags;
    
    Tag::Pointer _tag;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#include "DicomField.txx"

#endif // _42438b70_01c5_4513_b92d_1ea64bd22ef2
