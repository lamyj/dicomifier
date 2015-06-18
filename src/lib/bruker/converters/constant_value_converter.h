/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8456324b_169a_46f0_a62a_a673fa004fc1
#define _8456324b_169a_46f0_a62a_a673fa004fc1

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "bruker/converters/converter_base.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

/// @brief Create a DICOM element with a constant value
struct constant_value_converter: public converter_base
{
    dcmtkpp::Value value;

    constant_value_converter(dcmtkpp::Value const & value);

    virtual ~constant_value_converter();

    virtual void operator()(
        Dataset const & , FrameIndexGenerator const & ,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set);
};

}

}

}

#endif // _8456324b_169a_46f0_a62a_a673fa004fc1
