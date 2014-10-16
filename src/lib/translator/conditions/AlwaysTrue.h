/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7f858908_8448_4913_a39d_e0ff573c1b6e
#define _7f858908_8448_4913_a39d_e0ff573c1b6e

#include "ConditionBase.h"

namespace dicomifier
{
    
namespace translator
{
    
class AlwaysTrue : public ConditionBase
{
public:
    typedef AlwaysTrue Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomField
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~AlwaysTrue() {}
    
    virtual bool eval(DcmItem* dataset,
                      dicomifier::bruker::BrukerDataset* brukerdataset) 
        { return true; }

protected:
    AlwaysTrue() {}

private:
    
};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _7f858908_8448_4913_a39d_e0ff573c1b6e

