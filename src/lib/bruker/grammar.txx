/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7a1ad75a_ff4c_4b31_9d85_de443b73dcd9
#define _7a1ad75a_ff4c_4b31_9d85_de443b73dcd9

#include "grammar.h"

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace dicomifier
{
    
namespace bruker
{

template<typename TIterator>
grammar<TIterator>
::grammar()
: grammar::base_type(dataset)
{
    using boost::phoenix::push_back;
    
    using boost::spirit::qi::as_string;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::eol;
    using boost::spirit::qi::int_;
    using boost::spirit::qi::long_;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::_val;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ascii::space;
    
    // Do not use implicit action (i.e. %=): comments must be skipped
    dataset = (field[push_back(_val, _1)] | omit[comment]) % eol;
    
    // No parser action: we just ignore comments
    comment = "$$" >> +(~char_("\n"));
    
    field %= identifier >> "=" >> -shape >> omit[*space] >> value;
    identifier %= "##" >> -char_("$") >> +char_("a-zA-Z");
    // Shape has mandatory space after parenthesis to make a difference with array
    shape %= "(" >> omit[+space] >> (int_ % ("," >> *space)) >> omit[+space] >> ")";
    
    value %= numbers | quoted_strings | structs | unquoted_string;
    
    // Numbers *must* be separated with spaces, strings and structures but need
    // not since they have delimiters.
    numbers %= (real | long_) % +space;
    quoted_strings %= quoted_string % *space;
    structs %= struct_ % *space;
    
    // Unquoted strings stop at new line. Not sure if this is correct, the 
    // JCAMP-DX spec is not clear on this. 
    unquoted_string %= as_string[*(~char_("\n"))][push_back(_val, _1)];
    
    // Array has no space after parenthesis to make a difference with shape
    struct_ %= "(" >> (real | long_ | quoted_string | struct_) % ("," >> *space) >> ")";
    
    quoted_string %= "<" >> *( escaped_char | ~char_(">")) >> ">";
    escaped_char %= "\\" >> (char_(">\\") | eol);
}

} // namespace bruker

} // namespace dicomifier

#endif // _7a1ad75a_ff4c_4b31_9d85_de443b73dcd9
