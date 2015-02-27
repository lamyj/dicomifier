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
    
/**
 * @brief The ConditionBase class: Abstract base class for the conditions
 */
class ConditionBase : public Tag
{
public:
    typedef ConditionBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Destroy the instance of ConditionBase
    virtual ~ConditionBase();
    
    /**
     * @brief run: nothing to do
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
                     
    /**
     * @brief eval: Evaluate the condition
     * @param dataset: DICOM data
     * @param brukerdataset: Bruker data
     * @return true if condition is met, false otherwise
     */
    virtual bool eval(DcmItem* dataset,
                      dicomifier::bruker::Dataset* brukerdataset) = 0;

protected:
    /// Create an instance of ConditionBase
    ConditionBase();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _93aa4793_d803_4a11_a1d9_94f46b1b8961
