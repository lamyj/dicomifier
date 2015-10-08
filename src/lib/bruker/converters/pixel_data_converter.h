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

#include "bruker/Dataset.h"

namespace dicomifier
{

namespace bruker
{

class pixel_data_converter
{
public:
    pixel_data_converter();

    virtual ~pixel_data_converter();

    void operator()(unsigned int frame_size, unsigned int frame_index,
                    std::string const & filename, std::string const & word_type,
                    std::string const & file_byte_order,
                    dcmtkpp::DataSet & dicom_data_set);

    double get_rescaleintercept() const;

    double get_rescaleslope() const;

private:
    typedef uint16_t OutputPixelType;

    std::string _filename;
    dcmtkpp::Value::Binary _pixel_data;
    double _min;
    double _max;

    double _rescaleintercept;
    double _rescaleslope;

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

} // namespace bruker

} // namespace dicomifier

#include "pixel_data_converter.txx"

#endif // _e7c45dce_2bc3_47ba_93bd_017c50687fb4
