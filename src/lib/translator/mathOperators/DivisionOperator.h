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

/**
 * @brief The DivisionOperator class
 */
template<DcmEVR VR>
class DivisionOperator : public SubTag<VR>
{
public:
    typedef DivisionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DivisionOperator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of DivisionOperator
     * @param tags: Field to divide
     * @return new instance of DivisionOperator
     */
    static Pointer New(std::vector<Tag::Pointer> tags);

    /// Destroy the instance of DivisionOperator
    virtual ~DivisionOperator();
                     
    /**
     * @brief run: Divide some fields
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_DivisionOperator
     */
    virtual ClassType get_class_type() const { return ECT_DivisionOperator; }
    
protected:
    /// Create an instance of DivisionOperator
    DivisionOperator();
    
    /**
     * @brief Create an instance of DivisionOperator
     * @param tags: Field to divide
     */
    DivisionOperator(std::vector<Tag::Pointer> tags);

private:
    /// Field to divide
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "DivisionOperator.txx"

#endif // _a4e24b96_952f_4761_8641_d949e7f74a94
