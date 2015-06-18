/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0cffb65a_f943_409a_8b4a_428e70e7fbfa
#define _0cffb65a_f943_409a_8b4a_428e70e7fbfa

#include <functional>
#include <limits>
#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Element.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "bruker/converters/default_converter.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

template<typename TValue>
struct functor_converter: public default_converter
{
    typedef std::function<void(typename TValue::value_type &)> FunctionType;
    typedef TValue & (dcmtkpp::Element::*GetterType)();

    FunctionType function;
    GetterType getter;

    functor_converter(
        std::string const & bruker_tag, int type,
        FunctionType function, GetterType getter,
        int begin=-1, int end=std::numeric_limits<int>::max(), int item_size=1)
    : default_converter(bruker_tag, type, begin, end, item_size),
      function(function), getter(getter)
    {
        // Nothing else.
    }

    virtual ~functor_converter()
    {
        // Nothing to do.
    }

    virtual void operator()(
        Dataset const & bruker_data_set,
        FrameIndexGenerator const & index,
        dcmtkpp::Tag const & dicom_tag, dcmtkpp::VR const & vr,
        dcmtkpp::DataSet & dicom_data_set)
    {
        this->default_converter::operator()(
            bruker_data_set, index, dicom_tag, vr, dicom_data_set);
        if(dicom_data_set.has(dicom_tag))
        {
            auto & element = dicom_data_set[dicom_tag];
            for(unsigned int i=0; i<element.size(); ++i)
            {
                function((element.*getter)()[i]);
            }
        }
    }
};

}

}

}

#endif // _0cffb65a_f943_409a_8b4a_428e70e7fbfa
