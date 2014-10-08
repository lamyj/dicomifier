/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _88b8daec_f270_416f_b8c3_6f129d02bdca
#define _88b8daec_f270_416f_b8c3_6f129d02bdca

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace dicomifier
{
    
namespace bruker
{
    
struct BrukerValue;

typedef boost::variant<
            boost::recursive_wrapper<BrukerValue>,
            std::string
        > BrukerValue_node;

struct BrukerValue
{
    std::vector<BrukerValue_node> children;
};

} // namespace bruker

} // namespace dicomifier

// We need to tell fusion about our BrukerValue struct
// to make it a first-class fusion citizen
BOOST_FUSION_ADAPT_STRUCT(
    dicomifier::bruker::BrukerValue,
    (std::vector<dicomifier::bruker::BrukerValue_node>, children)
)

namespace dicomifier
{
    
namespace bruker
{
    
template <typename Iterator>
struct BrukerValue_grammar : boost::spirit::qi::grammar<Iterator, BrukerValue(), boost::spirit::ascii::space_type>
{
    BrukerValue_grammar() : BrukerValue_grammar::base_type(xml)
    {
        number_string = boost::spirit::no_skip[
                boost::spirit::ascii::char_("-+0-9")        [boost::spirit::qi::_val += boost::spirit::qi::_1]
            >>  *(boost::spirit::ascii::char_("0-9."))      [boost::spirit::qi::_val += boost::spirit::qi::_1]
            ];
            
        quoted_string = boost::spirit::no_skip[
                boost::spirit::qi::lit('<') 
            >>  *(boost::spirit::ascii::char_ - '>')        [boost::spirit::qi::_val += boost::spirit::qi::_1]
            >>  boost::spirit::qi::lit('>')
            ];
            
        other_string = boost::spirit::no_skip[
                (boost::spirit::ascii::char_("a-zA-Z0-9_")  [boost::spirit::qi::_val += boost::spirit::qi::_1]
            >>  *(boost::spirit::ascii::char_("a-zA-Z0-9_"))[boost::spirit::qi::_val += boost::spirit::qi::_1])
            ];
            
        struct_string =
                boost::spirit::qi::lit('(') 
            >>  xml                                         [boost::spirit::qi::_val = boost::spirit::qi::_1]
            >>  boost::spirit::qi::lit(')');
        
        node = 
                struct_string [boost::spirit::qi::_val = boost::spirit::qi::_1] |
                number_string [boost::spirit::qi::_val = boost::spirit::qi::_1] | 
                quoted_string [boost::spirit::qi::_val = boost::spirit::qi::_1] | 
                other_string  [boost::spirit::qi::_val = boost::spirit::qi::_1]
            ;
    
        // Remark: to be recursive, we should add -lit(',')
        //         Node could be separate by space or by comma (for struct_string)
        xml = *(-boost::spirit::qi::lit(',') >> node [boost::phoenix::push_back(boost::phoenix::at_c<0>(boost::spirit::qi::_val), boost::spirit::qi::_1)]);
    }

    boost::spirit::qi::rule<Iterator, BrukerValue(),        boost::spirit::ascii::space_type> xml;
    boost::spirit::qi::rule<Iterator, BrukerValue_node(),   boost::spirit::ascii::space_type> node;
    boost::spirit::qi::rule<Iterator, std::string(),        boost::spirit::ascii::space_type> number_string;
    boost::spirit::qi::rule<Iterator, std::string(),        boost::spirit::ascii::space_type> quoted_string;
    boost::spirit::qi::rule<Iterator, std::string(),        boost::spirit::ascii::space_type> other_string;
    boost::spirit::qi::rule<Iterator, BrukerValue_node(),   boost::spirit::ascii::space_type> struct_string;
};

} // namespace bruker

} // namespace dicomifier

#endif // _88b8daec_f270_416f_b8c3_6f129d02bdca
