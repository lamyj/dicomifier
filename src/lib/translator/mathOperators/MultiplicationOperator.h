/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c191dc73_6825_4307_86df_38c7ba2efa0a
#define _c191dc73_6825_4307_86df_38c7ba2efa0a

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class MultiplicationOperator : public SubTag<VR>
{
public:
    typedef MultiplicationOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of MultiplicationOperator
    static Pointer New();
    
    static Pointer New(std::vector<Tag::Pointer> tags);

    virtual ~MultiplicationOperator();
                     
    virtual void run(DcmDataset* dataset,
                     dicomifier::bruker::BrukerDataset* brukerdataset);
    
    virtual ClassType get_class_type() const { return ECT_MultiplicationOperator; }
    
protected:
    MultiplicationOperator();
    
    MultiplicationOperator(std::vector<Tag::Pointer> tags);

private:
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "MultiplicationOperator.txx"

#endif // _c191dc73_6825_4307_86df_38c7ba2efa0a
