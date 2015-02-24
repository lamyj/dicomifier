/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bd37797a_eb2b_4677_ae44_ef3d4b0380bf
#define _bd37797a_eb2b_4677_ae44_ef3d4b0380bf

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The ConstantField class
 */
template<DcmEVR VR>
class ConstantField : public SubTag<VR>
{
public:
    typedef ConstantField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    /// Create pointer to new instance of ConstantField
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of ConstantField
     * @param value: Single constant value
     * @return new instance of ConstantField
     */
    static Pointer New(ValueType const & value);
    
    /**
     * @brief Create pointer to new instance of ConstantField
     * @param array: multiple constant values
     * @return new instance of ConstantField
     */
    static Pointer New(ArrayType const & array);

    /// Destroy the instance of ConstantField
    virtual ~ConstantField();
    
    /**
     * @brief run: Nothing to do, values are inserted in Constructor
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of ConstantField
    ConstantField();
    
    /**
     * @brief Create an instance of ConstantField
     * @param value: Single constant value
     */
    ConstantField(ValueType const & value);
    
    /**
     * @brief Create an instance of ConstantField
     * @param array: multiple constant values
     */
    ConstantField(ArrayType const & array);

private:

};
} // namespace translator
    
} // namespace dicomifier

#include "ConstantField.txx"

#endif // _bd37797a_eb2b_4677_ae44_ef3d4b0380bf
