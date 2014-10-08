/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _719ceafd_9e20_455b_870f_ad693842fb37NEW
#define _719ceafd_9e20_455b_870f_ad693842fb37NEW
/*! \file BrukerFieldDataNEW.h
*/

#include <sstream>

#include "boost/regex.hpp"

#include "BrukerParser.h"

namespace dicomifier
{
    
namespace bruker
{

const boost::regex RegEx_KeyWord("^##\\$?([^[:cntrl:]]+)=.*");
const boost::regex RegEx_Dimensionnality("=\\( ([^[:cntrl:]]+) \\)");
const boost::regex RegEx_NotHeader("^##\\$[^[:cntrl:]]+=(.*)");
const boost::regex RegEx_Header("^##[^[:cntrl:]]+=(.*)");
const boost::regex RegEx_DeleteDimension("^\\( [^[:cntrl:]]+ \\)(.*)");

/**
 * \class BrukerFieldDataNEW
 * \brief This class is an atom to generate a BrukerDataSet
 */
class BrukerFieldData
{
public:
    typedef BrukerFieldData Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    static Pointer New(std::string value) 
        { return Pointer(new Self(value)); }
        
    static Pointer New(BrukerValue values) 
        { return Pointer(new Self(values)); }
    
    virtual ~BrukerFieldData();
    
    std::string Parse(std::string const& data);
    
    std::string get_data_type(int position = 0) const;
    
    std::string get_string(int position) const;
    int get_int(int position) const;
    double get_double(int position) const;
    Pointer get_struct(int position) const;
        
    inline BrukerValue get_brukervalues() const
        { return this->_brukervalues; }
        
    inline void set_brukervalues(BrukerValue values)
        { this->_brukervalues = values; }
        
    inline std::vector<int> get_dimensionNumbers() const
        { return this->_dimensionNumbers; }
        
    inline void set_dimensionNumbers(std::vector<int> dimensionNumbers)
        { this->_dimensionNumbers = dimensionNumbers; }
        
    int get_values_number() const;
    
    int parse_dimension(std::string const& data);
    
    int parse_values(std::string const& data);
                                           
protected:
    BrukerFieldData();
    
    BrukerFieldData(std::string value);
    
    BrukerFieldData(BrukerValue values);

private:
    /** 
     * Vector of int giving the dimension of each dimension of the 
     * keyword content 
     */
    std::vector<int> _dimensionNumbers;
    
    /**
     * Struct contains all values
     */
    BrukerValue _brukervalues;
    
};

} // namespace bruker

} // namespace dicomifier

#endif // _719ceafd_9e20_455b_870f_ad693842fb37

