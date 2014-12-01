/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8133a2ff_a47a_4d81_a631_f41b8161d901
#define _8133a2ff_a47a_4d81_a631_f41b8161d901

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class StackIDDcmField : public SubTag<VR>
{
public:
    typedef StackIDDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of StackIDDcmField
    static Pointer New();
    
    virtual ~StackIDDcmField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const 
            { return ECT_StackIDDcmField; }

protected:
    StackIDDcmField();

private:

};

} // namespace translator
    
} // namespace dicomifier

#include "StackIDDcmField.txx"

#endif // _8133a2ff_a47a_4d81_a631_f41b8161d901
