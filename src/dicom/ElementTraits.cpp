#include "ElementTraits.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#define DEFINE_ELEMENT_TRAITS(vr, value_type) \
typename ElementTraits<vr>::ElementSetterType const \
ElementTraits<vr> \
::element_setter = &DcmElement::put##value_type; \
typename ElementTraits<vr>::ElementArraySetterType const \
ElementTraits<vr> \
::element_array_setter = &DcmElement::put##value_type##Array;\
OFCondition \
ElementTraits<vr> \
::setter(DcmElement * element, ValueType const value) \
{ \
    return (element->*Self::element_setter)(value, 0); \
} \
OFCondition \
ElementTraits<vr> \
::array_setter(DcmElement * element, ValueType const * value, unsigned int const size) \
{ \
    return (element->*Self::element_array_setter)(value, size); \
}

#define DEFINE_STRING_ELEMENT_TRAITS(vr) \
OFCondition \
ElementTraits<vr> \
::setter(DcmElement * element, ValueType const value) \
{ \
    return Self::array_setter(element, &value, 1); \
} \
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

DEFINE_STRING_ELEMENT_TRAITS(EVR_AE)
DEFINE_STRING_ELEMENT_TRAITS(EVR_AS)
DEFINE_STRING_ELEMENT_TRAITS(EVR_CS)
DEFINE_STRING_ELEMENT_TRAITS(EVR_DS)
DEFINE_ELEMENT_TRAITS(EVR_FD, Float64)
DEFINE_ELEMENT_TRAITS(EVR_FL, Float32)
DEFINE_STRING_ELEMENT_TRAITS(EVR_IS)
DEFINE_ELEMENT_TRAITS(EVR_SL, Sint32)
DEFINE_ELEMENT_TRAITS(EVR_SS, Sint16)
DEFINE_ELEMENT_TRAITS(EVR_UL, Uint32)
DEFINE_ELEMENT_TRAITS(EVR_US, Uint16)

#undef DEFINE_ELEMENT_TRAITS
