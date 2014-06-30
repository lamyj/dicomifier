/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9b35ef04_0df7_49bc_81e6_c5e616af003e
#define _9b35ef04_0df7_49bc_81e6_c5e616af003e

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <vector>

/**
 * @brief Traits allowing generically getting and setting values inside a DICOM
 * element.
 *
 * All instantiations of this class shall define:
 *   * ValueType: the type of data stored in the element
 *   * ElementType: the DCMTK class derived from DcmElement corresponding to the VR
 *   * OFCondition setter(DcmElement * element, ValueType const value): a function setting the single value of an element
 *   * OFCondition array_setter(DcmElement * element, ValueType const * value, unsigned int const size): a function setting the array value of an element
 */
template<DcmEVR VR>
struct ElementTraits;

#define DECLARE_ELEMENT_TRAITS(vr, value_type, element_type) \
template<> \
struct ElementTraits<vr> \
{ \
    typedef ElementTraits<vr> Self; \
    typedef value_type ValueType; \
    typedef element_type ElementType; \
    typedef OFCondition (DcmElement::*ElementSetterType)(ValueType const, unsigned long const); \
    typedef OFCondition (DcmElement::*ElementArraySetterType)(ValueType const *, unsigned long const); \
    static ElementSetterType const element_setter; \
    static ElementArraySetterType const element_array_setter; \
    static OFCondition setter(DcmElement * element, ValueType const value); \
    static OFCondition array_setter(DcmElement * element, ValueType const * value, unsigned int const size); \
    static std::vector<ValueType> array_getter(DcmElement * element); \
};

#define DECLARE_STRING_ELEMENT_TRAITS(vr, value_type, element_type) \
template<> \
struct ElementTraits<vr> \
{ \
    typedef ElementTraits<vr> Self; \
    typedef value_type ValueType; \
    typedef element_type ElementType; \
    static OFCondition setter(DcmElement * element, ValueType const value); \
    static OFCondition array_setter(DcmElement * element, ValueType const * value, unsigned int const size); \
    static std::vector<ValueType> array_getter(DcmElement * element); \
};

DECLARE_STRING_ELEMENT_TRAITS(EVR_AE, OFString, DcmCodeString)
DECLARE_STRING_ELEMENT_TRAITS(EVR_AS, OFString, DcmCodeString)
DECLARE_STRING_ELEMENT_TRAITS(EVR_CS, OFString, DcmCodeString)
DECLARE_STRING_ELEMENT_TRAITS(EVR_DS, Float64, DcmDecimalString)
DECLARE_ELEMENT_TRAITS(EVR_FD, Float64, DcmFloatingPointDouble)
DECLARE_ELEMENT_TRAITS(EVR_FL, Float32, DcmFloatingPointSingle)
DECLARE_STRING_ELEMENT_TRAITS(EVR_IS, Sint32, DcmIntegerString)
DECLARE_ELEMENT_TRAITS(EVR_SL, Sint32, DcmSignedLong)
DECLARE_ELEMENT_TRAITS(EVR_SS, Sint16, DcmSignedShort)
DECLARE_ELEMENT_TRAITS(EVR_UL, Uint32, DcmUnsignedLong)
DECLARE_ELEMENT_TRAITS(EVR_US, Uint16, DcmUnsignedShort)

#undef DECLARE_ELEMENT_TRAITS
#undef DECLARE_STRING_ELEMENT_TRAITS

#endif // _9b35ef04_0df7_49bc_81e6_c5e616af003e
