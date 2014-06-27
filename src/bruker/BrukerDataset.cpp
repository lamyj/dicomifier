
#include <iostream>

#include "BrukerDataset.h"

namespace router
{
    
BrukerDataset::BrukerDataset()
{
}

BrukerDataset::BrukerDataset(BrukerDataset const & dataset)
{
    BrukerMapType::const_iterator iter = dataset.BrukerHeaderMap.begin();
    for (; iter != dataset.BrukerHeaderMap.end(); ++iter)
    {
        this->BrukerHeaderMap[ (*iter).first ] = (*iter).second;
    }
}

BrukerDataset::~BrukerDataset()
{
}

bool BrukerDataset::LoadFile(std::string fileToRead)
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

void BrukerDataset::Parse(std::string const & data)
{
    // Get first data position
    int PositionDebut = data.find("##");
    int PositionFin = PositionDebut + 2;
    if (PositionFin >= data.length())
        return;
        
    std::string Substring, currentKey;
    int PosRel = 0;
    
    BrukerFieldData currentData;
    
    // While all buffer not read
    while (PositionDebut != std::string::npos)
    {
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
        
        // Get data key
        currentKey = BrukerFieldData::MatchBufferForText(Substring, RegEx_KeyWord);
        
        // Get key data
        currentData.Parse(Substring);
        
        // Protection against duplication key
        if ( ! this->HasFieldData(currentKey))
        {
            this->BrukerHeaderMap[ currentKey ] = currentData;
        }
        else
        {
            // duplicate key with different value
            if (BrukerHeaderMap[ currentKey ].toString() != currentData.toString())
            {
                // error
                std::cout << "Key '" << currentKey << "' already exist." << std::endl;
                std::cout << "\tvalue1 = " << BrukerHeaderMap[ currentKey ].toString() << std::endl;
                std::cout << "\tvalue2 = " << currentData.toString() << std::endl;
            }
        }
        
        currentData.Reset();
    }
}

void BrukerDataset::Parse(std::istream & streamdata)
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

std::string BrukerDataset::toString() const
{
    std::ostringstream oss (std::ostringstream::out);
    
    BrukerMapType::const_iterator it = BrukerHeaderMap.begin();
    for (; it != BrukerHeaderMap.end(); ++it )
    {
        oss << (*it).first << "=";
        oss << (*it).second.toString() << "\n";
    } 
    
    return oss.str();
}

void BrukerDataset::SetFieldData(std::string const & key, 
                                 BrukerFieldData const & value)
{
    // Do not add non-existing key
    if (this->HasFieldData(key))
    {
        // Replace value
        BrukerHeaderMap[key] = value;
    }
}

BrukerFieldData BrukerDataset::GetFieldData(std::string key) const
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
    // throw an error ?
    return BrukerFieldData();
}

bool BrukerDataset::HasFieldData(std::string key) const
{
    // Search key
    BrukerMapType::const_iterator element;
    element = BrukerHeaderMap.find(key);
    // Return true if key exist, false otherwise
    return element != BrukerHeaderMap.end();
}

} // namespace router
