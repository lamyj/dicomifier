/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _38f2f367_9431_49ca_8af8_2b7a79e7198d
#define _38f2f367_9431_49ca_8af8_2b7a79e7198d

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The SubtractionOperator class
 */
template<DcmEVR VR>
class SubtractionOperator : public SubTag<VR>
{
public:
    typedef SubtractionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SubtractionOperator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of SubtractionOperator
     * @param tags: Fields to substract
     * @return new instance of SubtractionOperator
     */
    static Pointer New(std::vector<Tag::Pointer> tags);

    /// Destroy the instance of SubtractionOperator
    virtual ~SubtractionOperator();

    /**
     * @brief run: Substract some fields
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_SubtractionOperator
     */
    virtual ClassType get_class_type() const { return ECT_SubtractionOperator; }
    
protected:
    /// Create an instance of SubtractionOperator
    SubtractionOperator();
    
    /**
     * @brief Create an instance of SubtractionOperator
     * @param tags: Fields to substract
     */
    SubtractionOperator(std::vector<Tag::Pointer> tags);

private:
    /// Fields to substract
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "SubtractionOperator.txx"

#endif // _38f2f367_9431_49ca_8af8_2b7a79e7198d
