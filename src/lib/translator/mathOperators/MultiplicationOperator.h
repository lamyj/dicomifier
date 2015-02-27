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

/**
 * @brief The MultiplicationOperator class
 */
template<DcmEVR VR>
class MultiplicationOperator : public SubTag<VR>
{
public:
    typedef MultiplicationOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of MultiplicationOperator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of MultiplicationOperator
     * @param tags: Field to multiply
     * @return new instance of MultiplicationOperator
     */
    static Pointer New(std::vector<Tag::Pointer> tags);

    /// Destroy the instance of MultiplicationOperator
    virtual ~MultiplicationOperator();
                     
    /**
     * @brief run: Multiply some fields
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of MultiplicationOperator
    MultiplicationOperator();
    
    /**
     * @brief Create an instance of MultiplicationOperator
     * @param tags: Field to multiply
     */
    MultiplicationOperator(std::vector<Tag::Pointer> tags);

private:
    /// Field to multiply
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "MultiplicationOperator.txx"

#endif // _c191dc73_6825_4307_86df_38c7ba2efa0a
