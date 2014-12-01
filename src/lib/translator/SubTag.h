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
    
template<DcmEVR VR>
class SubTag : public Tag
{
public:
    typedef SubTag Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    virtual ~SubTag();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset) = 0;
    
    virtual ClassType get_class_type() const = 0;

    ArrayType get_array() const;
    
protected:
    SubTag();

    ArrayType _array;
    
private:

};
    
} // namespace translator

} // namespace dicomifier

#include "SubTag.txx"

#endif // _cc65448b_8e38_4ce0_bf60_0cb97f65641a
