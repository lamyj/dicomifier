/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _96ec3f5b_4adf_4b11_9f29_8fa10923df12
#define _96ec3f5b_4adf_4b11_9f29_8fa10923df12

#include <limits>
#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/Field.h"
#include "bruker/converters/converter_base.h"
#include "bruker/Dataset.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

/// @brief Convert a single Bruker field to DICOM.
struct default_converter: public converter_base
{
    /// @brief Bruker field to convert.
    std::string bruker_tag;

    /// @brief DICOM type of the element (1, 2 or 3).
    int type;

    /// @brief Index of the first element of each field item.
    int begin;

    /// @brief Index of the one-past-the last element of each field item.
    int end;

    /// @brief Number of elements in each item.
    int item_size;

    default_converter(
        std::string const & bruker_tag, int type,
        int begin=-1, int end=std::numeric_limits<int>::max(),
        int item_size=1);

    virtual ~default_converter();

    virtual void operator()(
        Dataset const & bruker_data_set,
        FrameIndexGenerator::Index const & index,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set);

    static void append_to_value(
        Field const & field, unsigned int index, dcmtkpp::Value & value);

};

}

}

}

#endif // _96ec3f5b_4adf_4b11_9f29_8fa10923df12
