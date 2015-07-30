/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e7c45dce_2bc3_47ba_93bd_017c50687fb4
#define _e7c45dce_2bc3_47ba_93bd_017c50687fb4

#include <string>

#include <dcmtkpp/DataSet.h>
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

class pixel_data_converter: public converter_base
{
public:
    pixel_data_converter();

    virtual ~pixel_data_converter();

    virtual void operator()(
        Dataset const & bruker_data_set,
        FrameIndexGenerator const & index,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set);

    void operator()(unsigned int frame_size, unsigned int frame_index,
                    std::string const & filename, std::string const & word_type,
                    std::string const & file_byte_order,
                    dcmtkpp::DataSet & dicom_data_set);

private:
    typedef uint16_t OutputPixelType;

    std::string _filename;
    dcmtkpp::Value::Binary _pixel_data;
    double _min;
    double _max;

    void _set_data_set(std::string const & filename,
                       std::string const & word_type,
                       std::string const & file_byte_order);

    template<typename TPixelType>
    dcmtkpp::Value::Binary _read_pixel_data(
        unsigned int frame_size, unsigned int index) const;

    template<typename TPixelType>
    void _flip();

    template<typename TPixelType>
    void _update_min_max();

};

}

}

}

#include "pixel_data_converter.txx"

#endif // _e7c45dce_2bc3_47ba_93bd_017c50687fb4
