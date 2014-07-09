/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _719ceafd_9e20_455b_870f_ad693842fb37
#define _719ceafd_9e20_455b_870f_ad693842fb37
/*! \file BrukerFieldData.h
*/

#include <sstream>

#include "boost/regex.hpp"

namespace dicomifier
{
    
namespace bruker
{

const boost::regex RegEx_KeyWord("^##\\$?([^[:cntrl:]]+)=.*");
const boost::regex RegEx_Dimensionnality("=\\( ([^[:cntrl:]]+) \\)");
const boost::regex RegEx_SignedInteger("(\\-?[0-9]+)");
const boost::regex RegEx_UnsignedInteger("([0-9]+)");
const boost::regex RegEx_BufferNValues("^##\\$?[^[:cntrl:]]+=\\( [^[:cntrl:]]+ \\)[[:space:]]*[[:cntrl:]]*([^[.dollar-sign.]]+).*");
const boost::regex RegEx_Buffer1Value("^##\\$?[^[:cntrl:]]+=(.*)");
const boost::regex RegEx_IntOrFloat("([\\-\\+eE0-9\\.]+)");

/**
 * \class BrukerFieldData
 * \brief This class is an atom to generate a BrukerDataSet
 */
class BrukerFieldData
{
public:
    /**
     * Constructor
     */
    BrukerFieldData();
    
    BrukerFieldData(std::string value);
    BrukerFieldData(int value);
    
    /**
     * Destructor
     */
    virtual ~BrukerFieldData();
    
    void Parse(std::string const& data);
    
    void Reset();
    
    std::string toString() const;
    
    /**
     * Modify attribut DimensionNumber
     * @param dimensionNb : new value
     */
    inline void SetDimensionNumber(const int dimensionNb) 
        { this->DimensionNumber = dimensionNb; }
    
    /**
     * Return attribut DimensionNumber
     * @return DimensionNumber
     */
    inline int GetDimensionNumber() const
        { return DimensionNumber; }
        
    /**
     * Modify attribut DataType
     * @param datatype : new value
     */
    inline void SetDataType(std::string const & datatype)
        { this->DataType = datatype; }
        
    /**
     * Return attribut DataType
     * @return DataType
     */
    inline std::string GetDataType() const
        { return this->DataType; }
        
    /**
     * Modify attribut NumberOfElements
     * @param nbofelements : new value
     */
    inline void SetNumberOfElements(const int nbofelements) 
        { this->NumberOfElements = nbofelements; }
    
    /**
     * Return attribut NumberOfElements
     * @return NumberOfElements
     */
    inline int GetNumberOfElements() const
        { return NumberOfElements; }
        
    inline std::vector<std::string> GetStringValue() const
        { return this->StringValue; }
        
    inline std::vector<int> GetIntValue() const
        { return this->IntValue; }
        
    inline std::vector<double> GetDoubleValue() const
        { return this->DoubleValue; }
    
    /**
     * 
     */ 
    static std::string SearchBufferForText(std::string const & kw, 
                                           const boost::regex& RegExp);
                                           
    /**
     * 
     */ 
    static std::string MatchBufferForText(std::string const & file,
                                          const boost::regex& RegExp);
                                          
    static void CleanString(std::string & str);
                                          
    std::string GetValueToString(bool clean = false) const;

protected:

private:
    /**
     * Return value dimensionnality
     * @param file : input buffer
     * @return value dimensionnality
     */                     
    int GetDimensionnality(std::string const & file);
    
    /**
     * Return value content type
     * @param file : input buffer
     * @return value Content type
     */
    std::string GetContentType(std::string const & file);
    
    /**
     * Return value part for a given key=value
     * @param file : input buffer
     * @return value part
     */
    std::string GetValuesPart(std::string const & file);
    
    /**
     * Return number of elements for a given string
     * @param file : input buffer
     * @return number of elements
     */
    int GetKeywordNumberOfElements(std::string const & file);
    
    /**
     * 
     * @param file : input buffer
     * @param N : Dimensionnality
     * @return 
     */
    int GetIntValueOfDimN(std::string const & file, int N);
    
    int GetIntValueN(std::string const & file,int N);
    
    double GetDoubleValueN(std::string const & file, int N);
    
    /**
     * Remove all newline
     * @param file : input buffer
     * @return buffer without newline
     */
    std::string RemoveNewlines(std::string file);
    
    /**
     * Dimmensionnality of the keyword
     */
    int DimensionNumber;
    
    /** 
     * Datatype of the keyword content
     */
    std::string DataType;
    
    /**
     * Total number of elements contained in keyword
     */
    int NumberOfElements;
    
    /** 
     * Vector of int giving the dimension of each dimension of the 
     * keyword content 
     */
    std::vector<int> DimensionNumberValue;
    
    /**
     * Vector of string containing the elements of keyword if they are string
     */
    std::vector<std::string> StringValue;
    
    /**
     * Vector of int containing the elements of keyword if they are int
     */
    std::vector<int> IntValue;
    
    /**
     * Vector of double containing the elements of keyword if they are float
     */
    std::vector<double> DoubleValue;
    
};

} // namespace bruker

} // namespace dicomifier

#endif // _719ceafd_9e20_455b_870f_ad693842fb37
