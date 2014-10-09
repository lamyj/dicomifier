/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _93aa4793_d803_4a11_a1d9_94f46b1b8961
#define _93aa4793_d803_4a11_a1d9_94f46b1b8961

#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
class ConditionBase : public Tag
{
public:
    typedef ConditionBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    virtual ~ConditionBase();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
                     
    virtual bool eval(DcmDataset* dataset,
                      dicomifier::bruker::BrukerDataset* brukerdataset) = 0;
    
    virtual ClassType get_class_type() const { return ECT_Unknown; }

protected:
    ConditionBase();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _93aa4793_d803_4a11_a1d9_94f46b1b8961
