/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d0e74fe3_4004_4df7_8c6c_c07ad4b5a8de
#define _d0e74fe3_4004_4df7_8c6c_c07ad4b5a8de

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class AdditionOperator : public SubTag<VR>
{
public:
    typedef AdditionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of AdditionOperator
    static Pointer New();
    
    static Pointer New(std::vector<Tag::Pointer> tags);

    virtual ~AdditionOperator();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_AdditionOperator; }
    
protected:
    AdditionOperator();
    
    AdditionOperator(std::vector<Tag::Pointer> tags);

private:
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "AdditionOperator.txx"

#endif // _d0e74fe3_4004_4df7_8c6c_c07ad4b5a8de
