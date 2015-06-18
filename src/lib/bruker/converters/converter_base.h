/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0eaac050_36d0_44c5_8a4c_640c9369673f
#define _0eaac050_36d0_44c5_8a4c_640c9369673f

#include <memory>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

/// @brief Base class for all Bruker-to-DICOM converters.
struct converter_base
{
    typedef std::shared_ptr<converter_base> pointer;

    virtual ~converter_base();

    virtual void operator()(
        Dataset const & bruker_data_set,
        FrameIndexGenerator::Index const & index,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set) =0;
};

}

}

}

#endif // _0eaac050_36d0_44c5_8a4c_640c9369673f
