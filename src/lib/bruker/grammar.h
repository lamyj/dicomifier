/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _16f1fd3a_de17_4351_9ce9_6cadd35bcdd5
#define _16f1fd3a_de17_4351_9ce9_6cadd35bcdd5

#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>

#include "Field.h"

namespace dicomifier
{
    
namespace bruker
{

/**
 * @brief Grammar based on boost::spirit to parse a Bruker data file.
 */
template<typename TIterator>
class grammar: public boost::spirit::qi::grammar<TIterator, std::vector<Field>()>
{
public:
    grammar();

private:
    template <typename T>
    struct strict_real_policies: boost::spirit::qi::real_policies<T>
    {
        static bool const expect_dot = true;
    };
    
    boost::spirit::qi::rule<TIterator, std::vector<Field>()> dataset;
    
    boost::spirit::qi::rule<TIterator> comment;
    
    boost::spirit::qi::rule<TIterator, Field()> field;
    boost::spirit::qi::rule<TIterator, std::string()> identifier;
    boost::spirit::qi::rule<TIterator, std::vector<int>()> shape;
    
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> value;
    
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> numbers;
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> quoted_strings;
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> atoms;
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> structs;
    
    boost::spirit::qi::rule<TIterator, std::string()> unquoted_string;
    boost::spirit::qi::rule<TIterator, std::vector<Field::Item>()> struct_;
    
    boost::spirit::qi::rule<TIterator, std::string()> quoted_string;
    boost::spirit::qi::rule<TIterator, char()> escaped_char;
    
    boost::spirit::qi::rule<TIterator, std::string()> atom;

    boost::spirit::qi::real_parser<float, strict_real_policies<float> > real;
};

} // namespace bruker

} // namespace dicomifier

#include "grammar.txx"

#endif // _16f1fd3a_de17_4351_9ce9_6cadd35bcdd5

