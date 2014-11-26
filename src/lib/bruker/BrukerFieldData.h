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
const boost::regex RegEx_Integer("^[0-9]+$");

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
    
    /// Create pointer to new instance of BrukerFieldData
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * @brief New: Create pointer to new instance of BrukerFieldData
     * @param value: value of this instance
     * @return
     */
    static Pointer New(std::string value) 
        { return Pointer(new Self(value)); }
        
    /**
     * @brief New: Create pointer to new instance of BrukerFieldData
     * @param values: values of this instance
     * @return
     */
    static Pointer New(BrukerValue values) 
        { return Pointer(new Self(values)); }
    
    /// Destroy the instance of BrukerFieldData
    virtual ~BrukerFieldData();
    
    /**
     * @brief Parse: Parse a given string data
     * @param data: Bruker field as string (Paravision Format)
     * @return Name of the bruker field
     */
    std::string Parse(std::string const& data);
    
    /**
     * @brief get_data_type: return the type of value
     * @param position: index of value
     * @return type of value as string
     */
    std::string get_data_type(int position = 0) const;
    
    /**
     * @brief get_string: return value as string
     * @param position: index of value
     * @return value as string of given index
     */
    std::string get_string(int position) const;

    /**
     * @brief get_int: return value as integer
     * @param position: index of value
     * @return value as integer of given index
     */
    int get_int(int position) const;

    /**
     * @brief get_double: return value as double
     * @param position: index of value
     * @return value as double of given index
     */
    double get_double(int position) const;

    /**
     * @brief get_struct: return value as BrukerFieldData
     * @param position: index of value
     * @return value as BrukerFieldData of given index
     */
    Pointer get_struct(int position) const;
        
    /**
     * @brief get_brukervalues: getter for brukerValues
     * @return brukerValues
     */
    inline BrukerValue get_brukervalues() const
        { return this->_brukervalues; }
        
    /**
     * @brief set_brukervalues: setter for brukerValues
     * @param values: new values
     */
    inline void set_brukervalues(BrukerValue values)
        { this->_brukervalues = values; }
        
    /**
     * @brief get_dimensionNumbers: getter for dimensionNumbers
     * @return dimensionNumbers
     */
    inline std::vector<int> get_dimensionNumbers() const
        { return this->_dimensionNumbers; }
        
    /**
     * @brief set_dimensionNumbers: setter for dimensionNumbers
     * @param dimensionNumbers: new values
     */
    inline void set_dimensionNumbers(std::vector<int> dimensionNumbers)
        { this->_dimensionNumbers = dimensionNumbers; }
        
    /**
     * @brief get_values_number: return total number of values
     * @return total number of values
     */
    int get_values_number() const;
    
    /**
     * @brief parse_dimension: parse Paravision field to identify cardinality
     * @param data: Paravision Field
     * @param deleteDim: (out) indicate if cardinality exists
     * @return cardinality
     */
    int parse_dimension(std::string const& data, bool & deleteDim);
    
    /**
     * @brief parse_values: parse Paravision field to identify values
     * @param data: Paravision Field
     * @param deleteDim: indicate if cardinality exists
     * @return number of values
     */
    int parse_values(std::string const& data, bool deleteDim);
                                           
protected:
    /**
     * @brief Create an instance of BrukerFieldData
     */
    BrukerFieldData();
    
    /**
     * @brief Create an instance of BrukerFieldData
     * @param value: value of this field
     */
    BrukerFieldData(std::string value);
    
    /**
     * @brief Create an instance of BrukerFieldData
     * @param values: values of this field
     */
    BrukerFieldData(BrukerValue values);

private:
    /** 
     * Vector of int giving the numbers of values
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

