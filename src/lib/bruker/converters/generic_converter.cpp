/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/generic_converter.h"

#include <functional>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "bruker/converters/converter_base.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

generic_converter
::generic_converter(Converter converter)
: converter_base(), converter(converter)
{
    // Nothing else.
}

generic_converter
::~generic_converter()
{
    // Nothing to do.
}

void
generic_converter
::operator()(
    Dataset const & bruker_data_set,
    FrameIndexGenerator::Index const & index,
    dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
    dcmtkpp::DataSet & dicom_data_set)
{
    dcmtkpp::Value value;
    if(dcmtkpp::is_int(vr))
    {
        value = dcmtkpp::Value::Integers();
    }
    else if(dcmtkpp::is_real(vr))
    {
        value = dcmtkpp::Value::Reals();
    }
    else if(dcmtkpp::is_string(vr))
    {
        value = dcmtkpp::Value::Strings();
    }
    else
    {
        throw DicomifierException("Cannot convert "+dcmtkpp::as_string(vr));
    }

    this->converter(bruker_data_set, value);
    dicom_data_set.add(dicom_tag, dcmtkpp::Element(value, vr));
}

}

}

}
