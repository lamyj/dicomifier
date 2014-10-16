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
    
template<DcmEVR VR>
class ImagePositionPatientDcmField : public SubTag<VR>
{
public:
    typedef ImagePositionPatientDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ImagePositionPatientDcmField
    static Pointer New();
    
    virtual ~ImagePositionPatientDcmField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const 
            { return ECT_ImagePositionPatientDcmField; }
    
protected:
    ImagePositionPatientDcmField();

private:

};
    
} // namespace dicomifier

} // namespace translator

#include "ImagePositionPatientDcmField.txx"

#endif // _dd00a025_9feb_4e1d_822d_9a07c849e345
