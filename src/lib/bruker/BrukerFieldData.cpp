/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BrukerFieldData.h"

namespace dicomifier
{
    
BrukerFieldData::BrukerFieldData():
    DimensionNumber(0),
    DataType(""),
    NumberOfElements(0)
{
    this->Reset();
}

BrukerFieldData::BrukerFieldData(std::string value):
    DimensionNumber(0),
    DataType("string"),
    NumberOfElements(0)
{
    this->Reset();
    
    this->StringValue.push_back(value);
}

BrukerFieldData::BrukerFieldData(int value):
    DimensionNumber(0),
    DataType("int"),
    NumberOfElements(0)
{
    this->Reset();
    
    this->IntValue.push_back(value);
}

BrukerFieldData::~BrukerFieldData()
{
}

void BrukerFieldData::Parse(std::string const & data)
{
    this->SetDimensionNumber(this->GetDimensionnality(data));
    
    this->SetDataType(this->GetContentType(data));
    
    this->SetNumberOfElements(this->GetKeywordNumberOfElements(data));
    
    if(this->DataType == "string")
    {
        this->SetDimensionNumber(0);
        this->SetNumberOfElements(1);
    }
    
    int count = 0;
    while (count <= this->DimensionNumber)
    {
        this->DimensionNumberValue.push_back(GetIntValueOfDimN(data,count));
        count++;
    }
    
    for(int currentNb = 1; currentNb <= this->NumberOfElements; currentNb++)
    {
        if (this->DataType == "int") 
        { 
            int value = GetIntValueN(data,currentNb);
            this->IntValue.push_back(value);
            this->DoubleValue.push_back((double)value);
        }

        if (this->DataType == "float") 
        { 
            this->DoubleValue.push_back(GetDoubleValueN(data,currentNb));
        }
    }

    if (this->DataType == "string")
    { 
        this->StringValue.push_back(GetValuesPart(data));
    }
}

void BrukerFieldData::Reset()
{
    this->DimensionNumberValue.clear();
    this->IntValue.clear();
    this->DoubleValue.clear();
    this->StringValue.clear();
}

std::string BrukerFieldData::toString() const
{
    std::ostringstream oss (std::ostringstream::out);
    
    oss << "(DimensionNumber=" << this->DimensionNumber;
    oss << ",DataType=" << this->DataType;
    oss << ",NumberOfElements=" << this->NumberOfElements;
    oss << ",DimensionNumberValue=[" ;
    for (int i = 0 ; i < this->DimensionNumberValue.size() ; i++)
    {
        oss << this->DimensionNumberValue[i] << ",";
    }
    oss << "]";
    
    if (this->DataType == "string")
    {
        oss << ",StringValue=[" ;
        for (int i = 0 ; i < this->StringValue.size() ; i++)
        {
            oss << this->StringValue[i] << ",";
        }
        oss << "]";
    }
    else if (this->DataType == "int")
    {
        oss << ",IntValue=[" ;
        for (int i = 0 ; i < this->IntValue.size() ; i++)
        {
            oss << this->IntValue[i] << ",";
        }
        oss << "]";
    }
    else if (this->DataType == "float")
    {
        oss << ",DoubleValue=[" ;
        for (int i = 0 ; i < this->DoubleValue.size() ; i++)
        {
            oss << this->DoubleValue[i] << ",";
        }
        oss << "]";
    }
    
    oss << ")";
    
    return oss.str();
}

std::string BrukerFieldData::GetValueToString(bool clean) const
{
    std::string ret;
    
    if (this->GetDataType() == "string")
    {
        std::vector<std::string>::const_iterator it = this->StringValue.begin();
        for (; it != this->StringValue.end(); ++it)
        {
            std::string currentValue = (*it);
            if (clean)
            {
                BrukerFieldData::CleanString(currentValue);
            }
            ret != "" ? ret += "\\" + currentValue : ret = currentValue;
        }
    }
    else if (this->GetDataType() == "int")
    {
        std::vector<int>::const_iterator it = this->IntValue.begin();
        for (; it != this->IntValue.end(); ++it)
        {
            std::stringstream ss;
            ss << (*it);
            
            ret != "" ? ret += "\\" + ss.str() : ret = ss.str();
        }
    }
    else if (this->GetDataType() == "float")
    {
        std::vector<double>::const_iterator it = this->DoubleValue.begin();
        for (; it != this->DoubleValue.end(); ++it)
        {
            std::stringstream ss;
            ss << (*it);
            
            ret != "" ? ret += "\\" + ss.str() : ret = ss.str();
        }
    }
    
    return ret;
}

int BrukerFieldData::GetDimensionnality(std::string const & file)
{
    int iterator=0;
    std::string DimensionnalityBuffer = 
        BrukerFieldData::SearchBufferForText(file, RegEx_Dimensionnality);
    
    // No dimension
    if (DimensionnalityBuffer == "") 
        return iterator;
    
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    std::string::const_iterator start,end;
    start = DimensionnalityBuffer.begin();
    end = DimensionnalityBuffer.end();

    while (regex_search(start, end, what, RegEx_UnsignedInteger))
    {
        iterator++;
        start = what[0].second;
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    return iterator;
}

std::string BrukerFieldData::GetContentType(std::string const & file)
{
    std::string ValuesPart;
    boost::match_flag_type flags = boost::match_default; 
    std::string::const_iterator start, end;
    ValuesPart = GetValuesPart(file);
    start=ValuesPart.begin();
    end=ValuesPart.end();
    // boost regexp_match can not handle well what we want
    // so instead of looking for a match we will seek proof of a non int serie
    // i.e. check if we can find something else than than -0-9
    boost::regex isNotIntSerie("[^ \\-0-9]");
    boost::match_results<std::string::const_iterator> whatInt;
    if (!regex_search(start,end, whatInt, isNotIntSerie,flags)) 
        return "int";

    // if not int serie check if it's not a floats serie !!!

    boost::regex isNotFloatSerie("[^ \\-\\+\\.eE0-9]");
    boost::match_results<std::string::const_iterator> whatFloat;
    if (!regex_search(start,end, whatFloat, isNotFloatSerie,flags))
        return "float";

    // if not a float serie neither, it's a string !!!
    return "string"; 
}

std::string BrukerFieldData::GetValuesPart(std::string const & file)
{
    std::string Result = 
        BrukerFieldData::MatchBufferForText(file, RegEx_BufferNValues);
        
    if (Result != "")   
        return this->RemoveNewlines(Result);
        
    return BrukerFieldData::MatchBufferForText(file, RegEx_Buffer1Value);
}

int BrukerFieldData::GetKeywordNumberOfElements(std::string const & file)
{
    int NumberOfElements = 1;
    for (int i = 1; i <= GetDimensionnality(file); i++)
    {
        NumberOfElements *= GetIntValueOfDimN(file, i);
    }
    return NumberOfElements;
}

int BrukerFieldData::GetIntValueOfDimN(std::string const & file, int N)
{
    int iterator=0;
    std::string DimensionnalityBuffer = 
            BrukerFieldData::SearchBufferForText(file, RegEx_Dimensionnality);

    if (N < 1 || DimensionnalityBuffer=="") 
        return 0;

    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags= boost::match_default;
    std::string::const_iterator start,end;
    start = DimensionnalityBuffer.begin();
    end = DimensionnalityBuffer.end();

    for (int i=1;i<=N;i++)
    {
        regex_search(start,end, what, RegEx_UnsignedInteger);
        iterator++;
        start=what[0].second;
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    return atoi(std::string(what[1].first,what[1].second).c_str());
}

int BrukerFieldData::GetIntValueN(std::string const & file,int N)
{
    std::string ValuesPart = GetValuesPart(file);
    int iterator=0;
    if (N < 1 || ValuesPart == "") 
        return -32767;

    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    std::string::const_iterator start,end;
    start = ValuesPart.begin();
    end = ValuesPart.end();

    while (iterator != N)
    {
        regex_search(start,end, what, RegEx_SignedInteger);
        iterator++;
        start=what[0].second;
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    return (atoi((std::string(what[1].first,what[1].second)).c_str()));
}

double BrukerFieldData::GetDoubleValueN(std::string const & file, int N)
{
    std::string ValuesPart=GetValuesPart(file);
    int iterator=0;
    if (N < 1 || ValuesPart=="") 
        return 0;
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags= boost::match_default;
    std::string::const_iterator start,end;
    start=ValuesPart.begin();
    end=ValuesPart.end();

    while (iterator != N)
    {
        regex_search(start,end, what, RegEx_IntOrFloat);
        iterator++;
        start=what[0].second;
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    return (atof((std::string(what[1].first,what[1].second)).c_str()));
}

std::string BrukerFieldData::SearchBufferForText(
        std::string const & file, 
        const boost::regex& RegExp)
{
    boost::cmatch what;
    if (regex_search(file.c_str(), what, RegExp)) 
        return what[1];
    return "";
}

std::string BrukerFieldData::MatchBufferForText(
        std::string const & file,
        const boost::regex& RegExp)
{
    boost::cmatch what;
    if (regex_match(file.c_str(), what, RegExp)) 
        return what[1];
    return "";
}

void BrukerFieldData::CleanString(std::string & str)
{
    int l = str.size();
    if (str[l-1] == 0x0A || str[l-1] == 0x0D ) // CR or NL
    {
        l--;
        str = str.substr(0, l);
    }
    if (str[l-1] == ' ' ) // blank space
    {
        l--;
        str = str.substr(0, l);
    }   

    if (str[0] == '<')
    { 
        str= str.substr(1,l-2);
    }
}

std::string BrukerFieldData::RemoveNewlines(std::string file)
{
    boost::regex regexNewline;
    const char* pre_expression = "[[:cntrl:]]";
    regexNewline.assign(pre_expression);

    const char* pre_format = "";
    std::ostringstream t(std::ios::out | std::ios::binary);
    std::ostream_iterator<char, char> oi(t);
    boost::regex_replace(oi, file.begin(), file.end(),
                        regexNewline, pre_format, 
                        boost::match_default | boost::format_all);
    std::string s(t.str());
    return s;
 }

} // namespace dicomifier
