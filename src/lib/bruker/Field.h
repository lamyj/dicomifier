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
 *
 * A field is a container of named variant-typed items.
 */
class Field
{
public:
    /// @brief Variant-typed field item.
    typedef boost::make_recursive_variant<
        long, double, std::string,
        std::vector<boost::recursive_variant_>
    >::type Item;
    
    typedef std::vector<int> Shape;
    typedef std::vector<Item> Value;
    
    /// @brief Name of the field.
    std::string name;

    /// @brief Shape of the field.
    Shape shape;

    /// @brief Value of the field.
    Value value;
    
    /// @brief Create an empty, un-named, field.
    Field();

    /// @brief Creator.
    Field(std::string const & name, Shape const & shape, Value const & value);
    
    /// @brief Return a string item, throw an exception if not string-typed.
    std::string const & get_string(unsigned int index) const;

    /// @brief Return a int-convertible item, throw an exception if not convertible.
    long get_int(unsigned int index) const;

    /// @brief Return a real-convertible item, throw an exception if not convertible.
    double get_real(unsigned int index) const;

    /// @brief Return a struct item, throw an exception if not struct-typed.
    Value get_struct(unsigned int index) const;

    /// @brief Test whether item is an int.
    bool is_int(unsigned int index) const;

    /// @brief Test whether item is a real.
    bool is_real(unsigned int index) const;

    /// @brief Test whether item is a string.
    bool is_string(unsigned int index) const;

    /// @brief Test whether item is a struct.
    bool is_struct(unsigned int index) const;
    
    bool operator==(Field const & other) const;
    bool operator!=(Field const & other) const;
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
