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

/**
 * @brief The AdditionOperator class
 */
template<DcmEVR VR>
class AdditionOperator : public SubTag<VR>
{
public:
    typedef AdditionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of AdditionOperator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of AdditionOperator
     * @param tags: Field to be added
     * @return new instance of AdditionOperator
     */
    static Pointer New(std::vector<Tag::Pointer> tags);

    /// Destroy the instance of AdditionOperator
    virtual ~AdditionOperator();
                     
    /**
     * @brief run: add some field
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of AdditionOperator
    AdditionOperator();
    
    /**
     * @brief Create an instance of AdditionOperator
     * @param tags: Field to be added
     */
    AdditionOperator(std::vector<Tag::Pointer> tags);

private:
    /// Field to be added
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "AdditionOperator.txx"

#endif // _d0e74fe3_4004_4df7_8c6c_c07ad4b5a8de
