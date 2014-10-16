/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d53e7f39_7426_4135_85c1_f9349dc13342
#define _d53e7f39_7426_4135_85c1_f9349dc13342

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class TimeGenerator : public SubTag<VR>
{
public:
    typedef TimeGenerator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of TimeGenerator
    static Pointer New();

    virtual ~TimeGenerator();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const { return ECT_TimeGenerator; }
    
protected:
    TimeGenerator();

private:

};

} // namespace translator
    
} // namespace dicomifier

#include "TimeGenerator.txx"

#endif // _d53e7f39_7426_4135_85c1_f9349dc13342


