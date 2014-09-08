/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3633adcf_4ae2_485d_8f67_8cff655cd8d3
#define _3633adcf_4ae2_485d_8f67_8cff655cd8d3

#include "ConditionBase.h"

namespace dicomifier
{
    
namespace translator
{
    
class AlwaysFalse : public ConditionBase
{
public:
    typedef AlwaysFalse Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomField
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~AlwaysFalse() {}
    
    virtual bool eval(DcmDataset* dataset,
                      dicomifier::bruker::BrukerDataset* brukerdataset) 
        { return false; }

protected:
    AlwaysFalse() {}

private:
    
};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _3633adcf_4ae2_485d_8f67_8cff655cd8d3


