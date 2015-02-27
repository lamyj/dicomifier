/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _cc65448b_8e38_4ce0_bf60_0cb97f65641a
#define _cc65448b_8e38_4ce0_bf60_0cb97f65641a

#include "Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
/**
 * @brief The SubTag class: Abstact base class for translation SubTag
 */
template<DcmEVR VR>
class SubTag : public Tag
{
public:
    typedef SubTag Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    /// Destroy the instance of SubTag
    virtual ~SubTag();
    
    /**
     * @brief run: Call to execute translation. Should be override by inherit classes
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset) = 0;

    /**
     * @brief get_array: getter for attribut array
     * @return array
     */
    ArrayType get_array() const;
    
protected:
    /// Create an instance of SubTag
    SubTag();

    /// Values of this tag
    ArrayType _array;
    
private:

};
    
} // namespace translator

} // namespace dicomifier

#include "SubTag.txx"

#endif // _cc65448b_8e38_4ce0_bf60_0cb97f65641a
