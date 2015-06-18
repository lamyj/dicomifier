/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/default_converter.h"

#include <algorithm>
#include <iterator>
#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Element.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/Field.h"
#include "bruker/Dataset.h"
#include "bruker/converters/converter_base.h"
#include "core/DicomifierException.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

default_converter
::default_converter(
    std::string const & bruker_tag, int type, int begin, int end, int item_size)
: converter_base(), bruker_tag(bruker_tag), type(type), begin(begin), end(end),
  item_size(item_size)
{
    // Nothing else.
}

default_converter
::~default_converter()
{
    // Nothing to do.
}

void
default_converter
::operator()(
    Dataset const & bruker_data_set, FrameIndexGenerator::Index const & index,
    dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
    dcmtkpp::DataSet & dicom_data_set)
{
    if(!bruker_data_set.has_field(this->bruker_tag))
    {
        if(this->type == 1)
        {
            throw DicomifierException("Required field is missing");
        }
        else if(this->type == 2)
        {
            dicom_data_set.add(dicom_tag, dcmtkpp::Element(dcmtkpp::Value(), vr));
        }
        // Otherwise do nothing
    }
    else
    {
        auto const & field = bruker_data_set.get_field(this->bruker_tag);

        auto const & frame_groups = bruker_data_set.get_frame_groups();
        auto const frame_group_it = std::find_if(
            frame_groups.begin(), frame_groups.end(),
            [&](FrameGroup const & frame_group) {
                auto const it = std::find_if(
                    frame_group.parameters.begin(), frame_group.parameters.end(),
                    [&](FrameGroup::Parameter const & parameter) {
                        return (parameter.name == this->bruker_tag);
                    }
                );
                return (it != frame_group.parameters.end());
            }
        );

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

        int begin_item=0;
        int end_item=1;

        if(frame_group_it != frame_groups.end())
        {
            begin_item = index[std::distance(frame_groups.begin(), frame_group_it)];
            end_item = begin_item+1;
        }
        else
        {
            begin_item = 0;
            end_item = field.get_size()/this->item_size;
        }

        for(int item_it=begin_item; item_it != end_item; ++item_it)
        {
            for(int element_it=std::max(0, this->begin);
                element_it != std::min<int>(this->item_size, this->end);
                ++element_it)
            {
                this->append_to_value(
                    field, this->item_size*item_it+element_it, value);
            }
        }

        dicom_data_set.add(dicom_tag, dcmtkpp::Element(value, vr));
    }
}

void
default_converter
::append_to_value(
    Field const & field, unsigned int index, dcmtkpp::Value & value)
{
    if(value.get_type() == dcmtkpp::Value::Type::Integers)
    {
        value.as_integers().push_back(field.get_int(index));
    }
    else if(value.get_type() == dcmtkpp::Value::Type::Reals)
    {
        value.as_reals().push_back(field.get_float(index));
    }
    else if(value.get_type() == dcmtkpp::Value::Type::Strings)
    {
        value.as_strings().push_back(field.get_string(index));
    }
}

}

}

}
