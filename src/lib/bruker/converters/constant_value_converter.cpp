/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/constant_value_converter.h"

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Element.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/converters/converter_base.h"
#include "bruker/Dataset.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

constant_value_converter
::constant_value_converter(dcmtkpp::Value const & value)
: value(value)
{
    // Nothing else.
}

constant_value_converter
::~constant_value_converter()
{
    // Nothing to do;
}

void
constant_value_converter
::operator()(
    Dataset const & , FrameIndexGenerator::Index const & ,
    dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
    dcmtkpp::DataSet & dicom_data_set)
{
    dicom_data_set.add(dicom_tag, dcmtkpp::Element(this->value, vr));
}

}

}

}
