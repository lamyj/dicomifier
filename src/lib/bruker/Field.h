/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ccb8d9e2_23f3_4d6e_bc38_c6e09ca6a674
#define _ccb8d9e2_23f3_4d6e_bc38_c6e09ca6a674

#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace dicomifier
{
    
namespace bruker
{

/**
 * @brief A field (i.e. record in JCAMP-DX jargon) of a Bruker data set.
 */
class Field
{
public:
    typedef boost::make_recursive_variant<
        long, float, std::string,
        std::vector<boost::recursive_variant_>
    >::type Item;
    
    typedef std::vector<int> Shape;
    typedef std::vector<Item> Value;
    
    std::string name;
    Shape shape;
    Value value;
    
    Field();
    Field(std::string const & name, Shape const & shape, Value const & value);
    
    Shape::size_type get_size() const;
    
    std::string const & get_string(unsigned int index) const;
    long get_int(unsigned int index) const;
};

} // namespace bruker

} // namespace dicomifier

BOOST_FUSION_ADAPT_STRUCT(
    dicomifier::bruker::Field, 
    (std::string, name)
    (std::vector<int>, shape)
    (std::vector<dicomifier::bruker::Field::Item>, value)
)

#endif // _ccb8d9e2_23f3_4d6e_bc38_c6e09ca6a674
