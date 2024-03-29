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

#include <string>
#include <vector>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

#include "Field.h"

namespace dicomifier
{
    
namespace bruker
{

template<typename TIterator>
grammar<TIterator>
::grammar()
: grammar::base_type(dataset)
{
    using boost::phoenix::at_c;
    using boost::phoenix::end;
    using boost::phoenix::insert;
    using boost::phoenix::push_back;
    
    using boost::spirit::qi::as_string;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::eoi;
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
    
    // Do not use implicit action (i.e. %=): no shape for "scalar" fields
    field = identifier[at_c<0>(_val) = _1] >> "=" >> 
        (
            (shape[at_c<1>(_val) = _1] >> omit[*space] >> value[at_c<2>(_val) = _1]) | 
            structs[at_c<2>(_val) = _1] |
            quoted_string[push_back(at_c<2>(_val), _1)] |
            // WARNING: for non-shaped, non-struct, unquoted values, the syntax
            // is ambiguous. To avoid backtracking errors, match scalar reals
            // and integers only if they constitute the whole value.
            (real >> &(eol|eoi))[push_back(at_c<2>(_val), _1)] |
            (long_ >> &(eol|eoi))[push_back(at_c<2>(_val), _1)] |
            unquoted_string[push_back(at_c<2>(_val), _1)]
        );
    
    identifier %= "##" >> +(~char_("="));
    // Shape has mandatory space after parenthesis to make a difference with array
    shape %= "(" >> omit[+space] >> (int_ % ("," >> *space)) >> omit[+space] >> ")";
    
    value %= (numbers | quoted_strings | atoms | structs) >> omit[*char_(" ")];
    
    // No implicit action due to RLE
    numbers = (
            (real | long_)
                [push_back(_val, _1)]
            | rle
                [insert(_val, end(_val), at_c<0>(_1), at_c<1>(_1))]
        ) % +space;
    
    quoted_strings %= quoted_string % *space;
    atoms %= atom % +space;
    
    // Do not use implicit action, since std::vector<Field::Item> is convertible to Field::Item
    structs = struct_[push_back(_val, _1)] % *space;
    
    // Assume lines have been joined beforehand.
    unquoted_string %= as_string[*(~char_("\n"))];
    
    // Array has no space after parenthesis to make a difference with shape
    struct_ %= "(" >> (real | long_ | quoted_string | struct_) % ("," >> *space) >> ")";
    
    rle %= "@" >> long_ >> "*(" >> (real | long_) >> ")";
    
    quoted_string %= "<" >> *( escaped_char | ~char_(">")) >> ">";
    escaped_char %= "\\" >> (char_(">\\") | eol);
    
    atom %= +char_("a-zA-Z0-9_");
}

} // namespace bruker

} // namespace dicomifier

#endif // _7a1ad75a_ff4c_4b31_9d85_de443b73dcd9
