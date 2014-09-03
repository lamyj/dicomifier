/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bd37797a_eb2b_4677_ae44_ef3d4b0380bf
#define _bd37797a_eb2b_4677_ae44_ef3d4b0380bf

#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class ConstantField : public Tag
{
public:
    typedef ConstantField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    /// Create pointer to new instance of DicomField
    static Pointer New();
    
    static Pointer New(ValueType const & value);
    
    static Pointer New(ArrayType const & array);

    virtual ~ConstantField();
    
    virtual void run(DcmDataset* dataset,
                     dicomifier::bruker::BrukerDataset* brukerdataset);
    
    virtual ClassType get_class_type() const { return ECT_ConstantField; }
    
    ArrayType get_array() const;
    
protected:
    ConstantField();
    
    ConstantField(ValueType const & value);
    
    ConstantField(ArrayType const & array);

private:
    ArrayType _array;

};
} // namespace translator
    
} // namespace dicomifier

#include "ConstantField.txx"

#endif // _bd37797a_eb2b_4677_ae44_ef3d4b0380bf
