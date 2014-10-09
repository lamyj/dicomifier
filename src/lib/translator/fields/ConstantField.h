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
    
template<DcmEVR VR>
class ConstantField : public SubTag<VR>
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
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_ConstantField; }
    
protected:
    ConstantField();
    
    ConstantField(ValueType const & value);
    
    ConstantField(ArrayType const & array);

private:

};
} // namespace translator
    
} // namespace dicomifier

#include "ConstantField.txx"

#endif // _bd37797a_eb2b_4677_ae44_ef3d4b0380bf
