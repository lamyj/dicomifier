#include "ElementTraits.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

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

#define DEFINE_ELEMENT_TRAITS(vr, value_type) \
SETTER(vr, value_type) \
ARRAY_SETTER(vr, value_type) \
ARRAY_GETTER(vr, value_type)

#define DEFINE_STRING_ELEMENT_TRAITS(vr, value_type) \
SETTER(vr, value_type) \
STRING_ARRAY_SETTER(vr, value_type) \
ARRAY_GETTER(vr, value_type)

DEFINE_STRING_ELEMENT_TRAITS(EVR_AE, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_AS, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_CS, OFString)
DEFINE_STRING_ELEMENT_TRAITS(EVR_DS, Float64)
DEFINE_ELEMENT_TRAITS(EVR_FD, Float64)
DEFINE_ELEMENT_TRAITS(EVR_FL, Float32)
DEFINE_STRING_ELEMENT_TRAITS(EVR_IS, Sint32)
DEFINE_ELEMENT_TRAITS(EVR_SL, Sint32)
DEFINE_ELEMENT_TRAITS(EVR_SS, Sint16)
DEFINE_ELEMENT_TRAITS(EVR_UL, Uint32)
DEFINE_ELEMENT_TRAITS(EVR_US, Uint16)


#undef DEFINE_ELEMENT_TRAITS
#undef DEFINE_STRING_ELEMENT_TRAITS

#undef SETTER
#undef ARRAY_SETTER
#undef ARRAY_GETTER
