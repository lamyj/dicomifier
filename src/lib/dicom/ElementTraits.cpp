/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ElementTraits.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

namespace dicomifier
{

#define SETTER(vr, value_type) \
OFCondition \
ElementTraits<vr> \
::setter(DcmElement * element, ValueType const value) \
{ \
    return Self::array_setter(element, &value, 1); \
}

#define ARRAY_SETTER(vr, value_type) \
OFCondition \
ElementTraits<vr> \
::array_setter(DcmElement * element, ValueType const * value, unsigned int const size) \
{ \
    return element->put##value_type##Array(value, size); \
}

#define STRING_ARRAY_SETTER(vr, value_type) \
OFCondition \
ElementTraits<vr> \
::array_setter(DcmElement * element, ValueType const * value, unsigned int const size) \
{ \
    std::ostringstream stream; \
    stream.imbue(std::locale("C")); \
    for(unsigned int i=0; i<size; ++i) \
    { \
        stream << value[i]; \
        if(i<size-1) \
        { \
            stream << "\\"; \
        } \
    } \
    return element->putOFStringArray(stream.str().c_str()); \
}

#define ARRAY_GETTER(vr, value_type) \
std::vector<ElementTraits<vr>::ValueType> \
ElementTraits<vr> \
::array_getter(DcmElement * element) \
{ \
    std::vector<ValueType> returnVector; \
    for (unsigned long i = 0; i < element->getVM(); i++) \
    { \
        ValueType value; \
        element->get##value_type(value, i); \
        returnVector.push_back(value); \
    } \
    return returnVector; \
}

#define EQUAL(vr, value_type) \
bool \
ElementTraits<vr> \
::equal(ElementTraits<vr>::ValueType const & v1, ElementTraits<vr>::ValueType const & v2) \
{ \
    return v1 == v2; \
}

#define STRING_EQUAL(vr, value_type) \
bool \
ElementTraits<vr> \
::equal(ElementTraits<vr>::ValueType const & v1, ElementTraits<vr>::ValueType const & v2) \
{ \
    return regex_match(v2.c_str(), transform_regex(v1.c_str())); \
}

#define DEFINE_ELEMENT_TRAITS(vr, value_type) \
SETTER(vr, value_type) \
ARRAY_SETTER(vr, value_type) \
ARRAY_GETTER(vr, value_type) \
EQUAL(vr, value_type)

#define DEFINE_STRING_NUMBER_ELEMENT_TRAITS(vr, value_type) \
SETTER(vr, value_type) \
STRING_ARRAY_SETTER(vr, value_type) \
ARRAY_GETTER(vr, value_type) \
EQUAL(vr, value_type)

#define DEFINE_STRING_ELEMENT_TRAITS(vr, value_type) \
SETTER(vr, value_type) \
STRING_ARRAY_SETTER(vr, value_type) \
ARRAY_GETTER(vr, value_type) \
STRING_EQUAL(vr, value_type)


DEFINE_STRING_ELEMENT_TRAITS(EVR_AE, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_AS, OFString)
// TODO: EVR_AT
DEFINE_STRING_ELEMENT_TRAITS(EVR_CS, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_DA, OFString)
DEFINE_STRING_NUMBER_ELEMENT_TRAITS(EVR_DS, Float64)
DEFINE_STRING_ELEMENT_TRAITS(EVR_DT, OFString)
DEFINE_ELEMENT_TRAITS(EVR_FD, Float64)
DEFINE_ELEMENT_TRAITS(EVR_FL, Float32)
DEFINE_STRING_NUMBER_ELEMENT_TRAITS(EVR_IS, Sint32)
DEFINE_STRING_ELEMENT_TRAITS(EVR_LO, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_LT, OFString)
// TODO: OB
// TODO: OF
// TODO: OW
DEFINE_STRING_ELEMENT_TRAITS(EVR_PN, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_SH, OFString)
DEFINE_ELEMENT_TRAITS(EVR_SL, Sint32)
// TODO: SQ
DEFINE_ELEMENT_TRAITS(EVR_SS, Sint16)
DEFINE_STRING_ELEMENT_TRAITS(EVR_UI, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_TM, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_ST, OFString)
DEFINE_ELEMENT_TRAITS(EVR_UL, Uint32)
// TODO: UN
DEFINE_ELEMENT_TRAITS(EVR_US, Uint16)
DEFINE_STRING_ELEMENT_TRAITS(EVR_UT, OFString)


#undef DEFINE_ELEMENT_TRAITS
#undef DEFINE_STRING_NUMBER_ELEMENT_TRAITS
#undef DEFINE_STRING_ELEMENT_TRAITS

#undef SETTER
#undef ARRAY_SETTER
#undef STRING_ARRAY_SETTER
#undef ARRAY_GETTER
#undef EQUAL
#undef STRING_EQUAL

} // namespace dicomifier
