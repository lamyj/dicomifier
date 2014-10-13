/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>

#include "BrukerDataset.h"

namespace dicomifier
{
    
namespace bruker
{
    
BrukerDataset
::BrukerDataset()
{
    // Nothing to do
}

BrukerDataset
::BrukerDataset(BrukerDataset const & dataset)
{
    BrukerMapType::const_iterator iter = dataset.BrukerHeaderMap.begin();
    for (; iter != dataset.BrukerHeaderMap.end(); ++iter)
    {
        this->BrukerHeaderMap[ (*iter).first ] = (*iter).second;
    }
}

BrukerDataset
::~BrukerDataset()
{
    // Nothing to do
}

bool 
BrukerDataset
::LoadFile(std::string fileToRead)
{
    std::ifstream FID;
    
    // Open file
    FID.open(fileToRead.c_str(), std::ios::binary);
    if (FID.rdstate()==std::ios::failbit) 
    {// Error
        return false;
    }

    this->Parse(FID);
    
    // Close file
    FID.close();
    
    return true;
}

void 
BrukerDataset
::Parse(std::string const & data)
{
    // Get first data position
    int PositionDebut = data.find("##");
    int PositionFin = PositionDebut + 2;
    if (PositionFin >= data.length())
        return;
        
    std::string Substring, currentKey;
    int PosRel = 0;
    
    BrukerFieldData::Pointer currentData;
    
    // While all buffer not read
    while (PositionDebut != std::string::npos)
    {
        currentData = BrukerFieldData::New(); 
        
        // Get next data position
        PositionFin = data.find("##",PositionDebut+2);
        
        // no more data
        if (-1 == PositionFin) break ;
        
        // Get substring (current data)
        Substring = data.substr (PositionDebut,PositionFin-PositionDebut-1);
        
        // Erase comment line
        PosRel=Substring.find("$$",0);
        if (-1 != PosRel) 
        {
            Substring = Substring.substr(0,PosRel-1);
        }
        
        // Move position for next loop
        PositionDebut = PositionFin;
        
        // Parsing
        currentKey = currentData->Parse(Substring);
            
        // Protection against duplication key
        if ( ! this->HasFieldData(currentKey))
        {
            this->BrukerHeaderMap[ currentKey ] = currentData;
        }
        else
        {
#if DEBUG
            // duplicate key with different value
            /* TODO: redefined operator == and operator << 
            if (BrukerHeaderMap[ currentKey ] != currentData)
            {
                // error
                std::cout << "Key '" << currentKey << "' already exist." << std::endl;
                std::cout << "\tvalue1 = " << BrukerHeaderMap[ currentKey ] << std::endl;
                std::cout << "\tvalue2 = " << currentData << std::endl;
            }
            */
#endif
        }
    }
}

void 
BrukerDataset
::Parse(std::istream & streamdata)
{
    // File length
    streamdata.seekg (0, std::ios::end);
    int length = streamdata.tellg();
    
    // Back to begin
    streamdata.seekg (0, std::ios::beg);

    // Read file
    char * buffer = new char [length];
    streamdata.read (buffer,length);
    
    std::string loadedfile (buffer, length);
    
    delete [] buffer;
    
    // Parse string
    this->Parse(loadedfile);
}

void 
BrukerDataset
::SetFieldData(std::string const & key, BrukerFieldData::Pointer const value)
{
    // Do not add non-existing key
    if (this->HasFieldData(key))
    {
        // Replace value
        BrukerHeaderMap[key] = value;
    }
}

BrukerFieldData::Pointer
BrukerDataset
::GetFieldData(std::string key) const
{
    // Search key
    BrukerMapType::const_iterator element;
    element = BrukerHeaderMap.find(key);
    
    if (element != BrukerHeaderMap.end() )
    {
        // Key find
        return (*element).second;
    }
    
    // Key not find => return default data field
    // TODO: throw an error ?
    return BrukerFieldData::New();
}

bool 
BrukerDataset
::HasFieldData(std::string key) const
{
    // Search key
    BrukerMapType::const_iterator element;
    element = BrukerHeaderMap.find(key);
    // Return true if key exist, false otherwise
    return element != BrukerHeaderMap.end();
}

std::vector<int> 
BrukerDataset
::create_frameGroupLists(int & coreframecount)
{
    // read VisuFGOrderDescDim (int), VisuFGOrderDesc (string) and VisuGroupDepVals (string)
    if (!this->HasFieldData("VisuFGOrderDescDim")  ||
        !this->HasFieldData("VisuFGOrderDesc")     ||
        !this->HasFieldData("VisuGroupDepVals"))
    {
        throw dicomifier::DicomifierException("Corrupted Bruker Data");
    }
    // First: look the VisuFGOrderDescDim attribut (Number of frame groups)
    int frameGroupDim = this->GetFieldData("VisuFGOrderDescDim")->get_int(0);

    coreframecount = 1;
    
    std::vector<int> indexlists;
    // Second: look the VisuFGOrderDesc to compute frame count
    for (auto count = 0; count < frameGroupDim; count++)
    {
        VISU_FRAMEGROUP_TYPE currentGroup;
        
        dicomifier::bruker::BrukerFieldData::Pointer fielddata = 
            this->GetFieldData("VisuFGOrderDesc")->get_struct(count);
            
        currentGroup.length = fielddata->get_int(0);
        int start   = fielddata->get_int(3);
        int number  = fielddata->get_int(4);
        
        for (auto gdvcount = start; gdvcount < start+number; gdvcount++)
        {
            dicomifier::bruker::BrukerFieldData::Pointer fielddatadepvals = 
                this->GetFieldData("VisuGroupDepVals")->get_struct(gdvcount);
            currentGroup.groupDepVals.push_back
            (
                std::make_pair<std::string, int>(
                    fielddatadepvals->get_string(0),
                    fielddatadepvals->get_int(1)
                    )
            );
        }
        
        indexlists.push_back(currentGroup.length);
        coreframecount *= currentGroup.length;
         
        this->_frameGroupLists.push_back(currentGroup);
    }
    
    return indexlists;
}

void 
BrukerDataset
::get_indexForValue(std::string const & valuename,
                    int & indexposition,
                    int & startposition) const
{
    indexposition = -1;
    startposition = 0;
    int count = -1;
    for (auto currentGroup : this->_frameGroupLists)
    {
        count++;
        for (auto currentDepVals : currentGroup.groupDepVals)
        {
            if (currentDepVals.first == valuename)
            {
                startposition = currentDepVals.second;
                indexposition = count;
                return;
            }
        }
    }
}

} // namespace bruker

} // namespace dicomifier
