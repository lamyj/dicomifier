/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _03693b0c_d945_4c30_bd67_4ddf5ff79287
#define _03693b0c_d945_4c30_bd67_4ddf5ff79287

#include <functional>

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

struct generic_converter: public converter_base
{
    typedef
        std::function<void(Dataset const & dataset,dcmtkpp::Value & value)>
        ConverterWithoutIndex;

    typedef
        std::function<
            void(
                Dataset const & dataset,
                dicomifier::FrameIndexGenerator const & index,
                dcmtkpp::Value & value)>
        ConverterWithIndex;

    generic_converter(ConverterWithIndex converter);
    generic_converter(ConverterWithoutIndex converter);

    virtual ~generic_converter();

    virtual void operator()(
        Dataset const & bruker_data_set,
        FrameIndexGenerator const & index,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set);
private:
    enum class Mode { WITH_INDEX, WITHOUT_INDEX };

    ConverterWithIndex _converter_with_index;
    ConverterWithoutIndex _converter_without_index;
    Mode _mode;
};

}

}

}

#endif // _03693b0c_d945_4c30_bd67_4ddf5ff79287
