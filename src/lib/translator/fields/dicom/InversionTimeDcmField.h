/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c179d131_c9de_4bf9_ac7f_b3f8e6a4d351
#define _c179d131_c9de_4bf9_ac7f_b3f8e6a4d351

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class InversionTimeDcmField : public SubTag<VR>
{
public:
    typedef InversionTimeDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InversionTimeDcmField
    static Pointer New();
    
    virtual ~InversionTimeDcmField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const 
            { return ECT_InversionTimeDcmField; }

protected:
    InversionTimeDcmField();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#include "InversionTimeDcmField.txx"

#endif // _c179d131_c9de_4bf9_ac7f_b3f8e6a4d351
