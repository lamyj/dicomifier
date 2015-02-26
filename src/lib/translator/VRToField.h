/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2d98599_d214_4279_98d6_0b42c5e18451
#define _b2d98599_d214_4279_98d6_0b42c5e18451

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dicom/ElementTraits.h"

namespace dicomifier
{
    
namespace translator
{

template<DcmEVR VR>
struct VRToFieldType;

template<> struct VRToFieldType<EVR_AE> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_AS> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_AT> { typedef long Type; }; // FIXME
template<> struct VRToFieldType<EVR_CS> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_DA> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_DS> { typedef float Type; };
template<> struct VRToFieldType<EVR_DT> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_FD> { typedef float Type; };
template<> struct VRToFieldType<EVR_FL> { typedef float Type; };
template<> struct VRToFieldType<EVR_IS> { typedef long Type; };
template<> struct VRToFieldType<EVR_LO> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_LT> { typedef std::string Type; };
// TODO: OB
// TODO: OF
// TODO: OW
template<> struct VRToFieldType<EVR_PN> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_SH> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_SL> { typedef long Type; };
// TODO: SQ
template<> struct VRToFieldType<EVR_SS> { typedef long Type; };
template<> struct VRToFieldType<EVR_UI> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_TM> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_ST> { typedef std::string Type; };
template<> struct VRToFieldType<EVR_UL> { typedef long Type; };
// TODO: UN
template<> struct VRToFieldType<EVR_US> { typedef long Type; };
template<> struct VRToFieldType<EVR_UT> { typedef std::string Type; };

template<typename TSource, typename TDestination>
TDestination convert_field_item(TSource const & source)
{
    return TDestination(source);
}

template<>
OFString convert_field_item<std::string, OFString>(std::string const & source)
{
    return OFString(&source[0], source.size());
}

} // namespace translator

} // namespace dicomifier

#endif // _b2d98599_d214_4279_98d6_0b42c5e18451
