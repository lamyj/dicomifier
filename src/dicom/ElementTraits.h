#ifndef _9b35ef04_0df7_49bc_81e6_c5e616af003e
#define _9b35ef04_0df7_49bc_81e6_c5e616af003e

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

/**
 * @brief Traits allowing generically getting and setting values inside a DICOM
 * element.
 *
 * All instantiations of this class shall define:
 *   * ValueType: the type of data stored in the element
 *   * ElementType: the DCMTK class derived from DcmElement corresponding to the VR
 *   * OFCondition setter(DcmElement * element, ValueType const value): a function setting the single value of an element
 *   * OFCondition array_setter(DcmElement * element, ValueType const * value, unsigned int const size): a function setting the array value of an element
 *   * std::vector<ValueType> array_getter(DcmElement * element): function returning all the values of an element
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
    static OFCondition setter(DcmElement * element, ValueType const value); \
    static OFCondition array_setter(DcmElement * element, ValueType const * value, unsigned int const size); \
    static std::vector<ValueType> array_getter(DcmElement * element); \
};

DECLARE_ELEMENT_TRAITS(EVR_AE, OFString, DcmCodeString)
DECLARE_ELEMENT_TRAITS(EVR_AS, OFString, DcmCodeString)
DECLARE_ELEMENT_TRAITS(EVR_CS, OFString, DcmCodeString)
DECLARE_ELEMENT_TRAITS(EVR_DS, Float64, DcmDecimalString)
DECLARE_ELEMENT_TRAITS(EVR_FD, Float64, DcmFloatingPointDouble)
DECLARE_ELEMENT_TRAITS(EVR_FL, Float32, DcmFloatingPointSingle)
DECLARE_ELEMENT_TRAITS(EVR_IS, Sint32, DcmIntegerString)
DECLARE_ELEMENT_TRAITS(EVR_SL, Sint32, DcmSignedLong)
DECLARE_ELEMENT_TRAITS(EVR_SS, Sint16, DcmSignedShort)
DECLARE_ELEMENT_TRAITS(EVR_UL, Uint32, DcmUnsignedLong)
DECLARE_ELEMENT_TRAITS(EVR_US, Uint16, DcmUnsignedShort)

#undef DECLARE_ELEMENT_TRAITS

#endif // _9b35ef04_0df7_49bc_81e6_c5e616af003e
