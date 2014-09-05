/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9b35ef04_0df7_49bc_81e6_c5e616af003e
#define _9b35ef04_0df7_49bc_81e6_c5e616af003e

#include <vector>

#include <boost/algorithm/string.hpp>
#include "boost/regex.hpp"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/Object.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

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
    static bool equal(ValueType const & v1, ValueType const & v2); \
    static ValueType fromString(std::string const & value); \
    static std::string toString(ValueType const & value); \
    static ValueType subtraction(ValueType const & v1, ValueType const & v2); \
    static ValueType division(ValueType const & v1, ValueType const & v2); \
    static ValueType multiplication(ValueType const & v1, ValueType const & v2); \
};

DECLARE_ELEMENT_TRAITS(EVR_AE, OFString, DcmApplicationEntity)
DECLARE_ELEMENT_TRAITS(EVR_AS, OFString, DcmAgeString)
// TODO: EVR_AT
DECLARE_ELEMENT_TRAITS(EVR_CS, OFString, DcmCodeString)
DECLARE_ELEMENT_TRAITS(EVR_DA, OFString, DcmDate)
DECLARE_ELEMENT_TRAITS(EVR_DS, Float64, DcmDecimalString)
DECLARE_ELEMENT_TRAITS(EVR_DT, OFString, DcmDateTime)
DECLARE_ELEMENT_TRAITS(EVR_FD, Float64, DcmFloatingPointDouble)
DECLARE_ELEMENT_TRAITS(EVR_FL, Float32, DcmFloatingPointSingle)
DECLARE_ELEMENT_TRAITS(EVR_IS, Sint32, DcmIntegerString)
DECLARE_ELEMENT_TRAITS(EVR_LO, OFString, DcmLongString)
DECLARE_ELEMENT_TRAITS(EVR_LT, OFString, DcmLongText)
// TODO: OB
// TODO: OF
// TODO: OW
DECLARE_ELEMENT_TRAITS(EVR_PN, OFString, DcmPersonName)
DECLARE_ELEMENT_TRAITS(EVR_SH, OFString, DcmShortString)
DECLARE_ELEMENT_TRAITS(EVR_SL, Sint32, DcmSignedLong)
// TODO: SQ
DECLARE_ELEMENT_TRAITS(EVR_SS, Sint16, DcmSignedShort)
DECLARE_ELEMENT_TRAITS(EVR_UI, OFString, DcmUniqueIdentifier)
DECLARE_ELEMENT_TRAITS(EVR_TM, OFString, DcmTime)
DECLARE_ELEMENT_TRAITS(EVR_ST, OFString, DcmShortText)
DECLARE_ELEMENT_TRAITS(EVR_UL, Uint32, DcmUnsignedLong)
// TODO: UN
DECLARE_ELEMENT_TRAITS(EVR_US, Uint16, DcmUnsignedShort)
DECLARE_ELEMENT_TRAITS(EVR_UT, OFString, DcmUnlimitedText)

#undef DECLARE_ELEMENT_TRAITS

template<typename Action>
static void vr_dispatch(Action const & action, DcmEVR evr)
{
    if      (evr == EVR_AE) action.template run<EVR_AE>();
    else if (evr == EVR_AS) action.template run<EVR_AS>();
    // TODO: EVR_AT
    else if (evr == EVR_CS) action.template run<EVR_CS>();
    else if (evr == EVR_DA) action.template run<EVR_DA>();
    else if (evr == EVR_DS) action.template run<EVR_DS>();
    else if (evr == EVR_DT) action.template run<EVR_DT>();
    else if (evr == EVR_FD) action.template run<EVR_FD>();
    else if (evr == EVR_FL) action.template run<EVR_FL>();
    else if (evr == EVR_IS) action.template run<EVR_IS>();
    else if (evr == EVR_LO) action.template run<EVR_LO>();
    else if (evr == EVR_LT) action.template run<EVR_LT>();
    // TODO: EVR_OB
    // TODO: EVR_OF
    // TODO: EVR_OW
    else if (evr == EVR_PN) action.template run<EVR_PN>();
    else if (evr == EVR_SH) action.template run<EVR_SH>();
    else if (evr == EVR_SL) action.template run<EVR_SL>();
    else if (evr == EVR_SQ) action.template run<EVR_SQ>();
    else if (evr == EVR_SS) action.template run<EVR_SS>();
    else if (evr == EVR_UI) action.template run<EVR_UI>();
    else if (evr == EVR_TM) action.template run<EVR_TM>();
    else if (evr == EVR_ST) action.template run<EVR_ST>();
    else if (evr == EVR_UL) action.template run<EVR_UL>();
    // TODO: EVR_UN
    else if (evr == EVR_US) action.template run<EVR_US>();
    else if (evr == EVR_UT) action.template run<EVR_UT>();
    
    else throw DicomifierException("Unknown VR");
}

static boost::regex transform_regex(std::string const & value)
{
    std::string regex = value;
    // Escape "\\" first since we're using it to replace "."
    boost::replace_all(regex, "\\", "\\\\");
    // Escape "." second since we're using it to replace "*"
    boost::replace_all(regex, ".", "\\.");
    boost::replace_all(regex, "*", ".*");
    boost::replace_all(regex, "?", ".");
    // Escape other PCRE metacharacters
    boost::replace_all(regex, "^", "\\^");
    boost::replace_all(regex, "$", "\\$");
    boost::replace_all(regex, "[", "\\[");
    boost::replace_all(regex, "]", "\\]");
    boost::replace_all(regex, "(", "\\(");
    boost::replace_all(regex, ")", "\\)");
    boost::replace_all(regex, "+", "\\+");
    boost::replace_all(regex, "{", "\\{");
    boost::replace_all(regex, "}", "\\}");
    // Add the start and end anchors
    regex = "^"+regex+"$";
    
    return boost::regex(regex, boost::regex::icase);
}

} // namespace dicomifier

#endif // _9b35ef04_0df7_49bc_81e6_c5e616af003e
