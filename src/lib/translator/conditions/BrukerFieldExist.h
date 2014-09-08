/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _89f07c95_97f3_4d46_84fb_01b6a3305a04
#define _89f07c95_97f3_4d46_84fb_01b6a3305a04

#include "ConditionBase.h"

namespace dicomifier
{
    
namespace translator
{
    
class BrukerFieldExist : public ConditionBase
{
public:
    typedef BrukerFieldExist Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DicomField
    static Pointer New() { return Pointer(new Self()); }
    
    static Pointer New(std::string const & brukerFieldName)
        { return Pointer(new Self(brukerFieldName)); }
    
    virtual ~BrukerFieldExist();
    
    virtual bool eval(DcmDataset* dataset,
                      dicomifier::bruker::BrukerDataset* brukerdataset);

protected:
    BrukerFieldExist();
    
    BrukerFieldExist(std::string const & brukerfieldname);

private:
    std::string _brukerFieldName;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _89f07c95_97f3_4d46_84fb_01b6a3305a04
