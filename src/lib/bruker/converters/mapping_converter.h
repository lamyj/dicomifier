/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _71833bf2_86ff_431e_a2d8_a66734897290
#define _71833bf2_86ff_431e_a2d8_a66734897290

#include <functional>
#include <limits>
#include <map>
#include <string>

#include "bruker/converters/functor_converter.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

template<typename TValue>
struct mapping_converter: public functor_converter<TValue>
{
    typedef std::map<typename TValue::value_type, typename TValue::value_type> MapType;
    typedef typename functor_converter<TValue>::GetterType GetterType;

    MapType map;

    mapping_converter(
        std::string const & bruker_tag, int type, MapType const & map,
        GetterType getter,
        int begin=-1, int end=std::numeric_limits<int>::max(), int item_size=1)
    : functor_converter<TValue>(bruker_tag, type,
        std::bind(&mapping_converter::convert, this, std::placeholders::_1),
        getter, begin, end, item_size),
      map(map)
    {
        // Nothing else.
    }

    virtual ~mapping_converter()
    {
        // Nothing to do.
    }

    void convert(typename TValue::value_type & value) const
    {
        auto const iterator = this->map.find(value);
        if(iterator == this->map.end())
        {
            throw DicomifierException("No such element");
        }
        value = iterator->second;
    }
};

}

}

}

#endif // _71833bf2_86ff_431e_a2d8_a66734897290
