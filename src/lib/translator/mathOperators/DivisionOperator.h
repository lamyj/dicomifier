/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a4e24b96_952f_4761_8641_d949e7f74a94
#define _a4e24b96_952f_4761_8641_d949e7f74a94

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class DivisionOperator : public SubTag<VR>
{
public:
    typedef DivisionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DivisionOperator
    static Pointer New();
    
    static Pointer New(std::vector<Tag::Pointer> tags);

    virtual ~DivisionOperator();
                     
    virtual void run(DcmDataset* dataset,
                     dicomifier::bruker::BrukerDataset* brukerdataset);
    
    virtual ClassType get_class_type() const { return ECT_DivisionOperator; }
    
protected:
    DivisionOperator();
    
    DivisionOperator(std::vector<Tag::Pointer> tags);

private:
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "DivisionOperator.txx"

#endif // _a4e24b96_952f_4761_8641_d949e7f74a94
