/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/lexical_cast.hpp>

#include "BrukerDirectory.h"
#include "core/DicomifierException.h"
#include "dicom/actions/SetElement.h"
#include "dicom/TagAndRange.h"

namespace dicomifier
{
    
namespace bruker
{
    
BrukerDirectory::BrukerDirectory()
{
    _BrukerDatasetList.clear();
    
    // Authorized files (only this files could be parse)
    FilesToRead.push_back("subject");
    FilesToRead.push_back("acqp");
    FilesToRead.push_back("method");
    FilesToRead.push_back("imnd");
    FilesToRead.push_back("isa");
    FilesToRead.push_back("d3proc");
    FilesToRead.push_back("reco");
    FilesToRead.push_back("visu_pars");
}

BrukerDirectory::~BrukerDirectory()
{
    if (_BrukerDatasetList.size() > 0)
    {
        BrukerMapDirectory::iterator it = _BrukerDatasetList.begin();
        for (; it != _BrukerDatasetList.end(); ++it )
        {
            if ((*it).second != NULL)
            {
                delete (*it).second;
            }
        }
        
        _BrukerDatasetList.clear();
    }
}

int BrukerDirectory::CreateMap(std::string const & inputDir)
{
    BrukerDataset * mainDataset = new BrukerDataset();
    std::vector<std::string> subDirectoryName;
    
    // Create Main BrukerDataset
    boost::filesystem::directory_iterator it(inputDir), it_end;
    for(; it != it_end; ++it)
    {
        // If element is a file
        if(! boost::filesystem::is_directory( (*it) ) )
        {
            // Should we parse this file ?
            if (isFileToRead((*it).path().filename().c_str()))
            {// yes
                // Parse file
                std::string file = inputDir + 
                                   VALID_FILE_SEPARATOR + 
                                   std::string((*it).path().filename().c_str());
                mainDataset->LoadFile(file);
            }
        }
        // Else element is a directory
        else
        {
            if (isDirToParse((*it).path().filename().c_str()))
            {
                subDirectoryName.push_back((*it).path().filename().c_str());
            }
        }
    }
    
    // Create Studies BrukerDatasets
    if (subDirectoryName.size() != 0)
    {
        for (auto iter = subDirectoryName.begin(); iter != subDirectoryName.end(); ++iter)
        {            
            std::string file = inputDir + VALID_FILE_SEPARATOR + (*iter);
            
            if ((*iter) == "pdata")
            { // find reconstruction directory
                ParseReconstructionDirectory(mainDataset, file, "0");
            }
            else
            { // find series directory
                ParseSeriesDirectory(mainDataset, file, (*iter));
            }
        }
        delete mainDataset;
    }
    else
    {
        this->_BrukerDatasetList[ "main" ] = mainDataset;
    }
    
    return this->_BrukerDatasetList.size();
}

void 
BrukerDirectory
::ParseSeriesDirectory(BrukerDataset * bdataset,
                       std::string const & inputDir,
                       std::string const & StudyNumber)
{
    BrukerDataset * studyDataset = new BrukerDataset(*bdataset);
    std::vector<std::string> subDirectoryName;
    
    // Update Main BrukerDataset with current study data
    boost::filesystem::directory_iterator it(inputDir), it_end;
    for(; it != it_end; ++it)
    {
        // If element is a file
        if(! boost::filesystem::is_directory( (*it) ) )
        {
            // Should we parse this file ?
            if (isFileToRead((*it).path().filename().c_str()))
            {// yes
                // Parse file
                std::string file = inputDir + 
                                   VALID_FILE_SEPARATOR + 
                                   std::string((*it).path().filename().c_str());
                studyDataset->LoadFile(file);
            }
        }
        // Else element is a directory
        else
        {
            if (isDirToParse((*it).path().filename().c_str()))
            {
                subDirectoryName.push_back((*it).path().filename().c_str());
            }
        }
    }
    
    // Create series BrukerDatasets
    if (subDirectoryName.size() != 0)
    {
        for (auto iter = subDirectoryName.begin(); iter != subDirectoryName.end(); ++iter)
        {            
            std::string file = inputDir + VALID_FILE_SEPARATOR + (*iter);
            
            if ((*iter) == "pdata")
            { // find reconstruction directory
                ParseReconstructionDirectory(studyDataset, file, StudyNumber);
            }
        }
    }
}

void 
BrukerDirectory
::ParseReconstructionDirectory(BrukerDataset * bdataset,
                               std::string const & inputDir,
                               std::string const & StudyNumber)
{
    BrukerDataset * seriesdataset = new BrukerDataset(*bdataset);
    std::vector<std::string> subDirectoryName;
    
    // Update Main BrukerDataset with current serie data
    boost::filesystem::directory_iterator it(inputDir), it_end;
    for(; it != it_end; ++it)
    {
        // If element is a file
        if(! boost::filesystem::is_directory( (*it) ) )
        {
            // Should we parse this file ?
            if (isFileToRead((*it).path().filename().c_str()))
            {// yes
                // Parse file
                std::string file = inputDir + 
                                   VALID_FILE_SEPARATOR + 
                                   std::string((*it).path().filename().c_str());
                seriesdataset->LoadFile(file);
            }
        }
        // Else element is a directory
        else
        {
            if (isDirToParse((*it).path().filename().c_str()))
            {
                subDirectoryName.push_back((*it).path().filename().c_str());
            }
        }
    }
    
    // Create reconstruction BrukerDatasets
    if (subDirectoryName.size() != 0)
    {
        for (auto iter = subDirectoryName.begin(); iter != subDirectoryName.end(); ++iter)
        {
            BrukerDataset * dataset = new BrukerDataset(*seriesdataset);
            
            std::string file = inputDir + VALID_FILE_SEPARATOR + (*iter);
                    
            this->ParseDirectory(dataset, file);
            
            std::string name = (*iter);
            while (name.length() < 4)
            {
                name = "0" + name;
            }
            name = StudyNumber + name;
            
            this->_BrukerDatasetList[ name ] = dataset;
        }
    }
}

void BrukerDirectory::ParseDirectory(BrukerDataset * bdataset, 
                                     std::string const & inputDir)
{
    if (bdataset == NULL)
    {
        return;
    }
    
    // scan inputDir
    boost::filesystem::directory_iterator iter(inputDir), it_end;
    for(; iter != it_end; ++iter)
    {
        // If element is a file
        if(! boost::filesystem::is_directory( (*iter) ) )
        {
            // Should we parse this file ?
            if (isFileToRead((*iter).path().filename().c_str()))
            {// yes
                std::string file = inputDir + 
                                   VALID_FILE_SEPARATOR + 
                                   std::string((*iter).path().filename().c_str());
                // Parse file
                bdataset->LoadFile(file);
            }
            else if (std::string((*iter).path().filename().c_str()) == 
                     std::string("2dseq")) // binary file
            {
                std::string file = inputDir + 
                                   VALID_FILE_SEPARATOR + 
                                   std::string((*iter).path().filename().c_str());
                
                std::string data = "##PIXELDATA=" + file + "\n##END=\n";
                
                bdataset->Parse(data);
            }
        }
        // Else element is a directory
        else
        {
            // recursively scan directory
            std::string subdir = inputDir + 
                                 VALID_FILE_SEPARATOR + 
                                 std::string((*iter).path().filename().c_str());
            ParseDirectory(bdataset, subdir);
        }
    }
}

bool BrukerDirectory::isFileToRead(std::string const & file)
{
    return std::find(FilesToRead.begin(), 
                     FilesToRead.end(), file) != FilesToRead.end();
}

bool BrukerDirectory::isDirToParse(std::string const & dir)
{
    if (dir == "pdata")
    {
        return true;
    }
    
    try
    {
        unsigned int result = std::stoul(dir);
        if (0 < result && result < 1000)
        {
            return true;
        }
    }
    catch (std::exception &e)
    {
    }
    
    return false;
}

void BrukerDirectory::getImgDataType(std::string const & wordtype,
                                     std::string const & byteorder,
                                     int & pixelSize,
                                     int & bitsallocated,
                                     int & bitsstored,
                                     int & highbit,
                                     int & pixelrepresentation)
{
    pixelrepresentation = 1;
    if (wordtype == "_32BIT_SGN_INT")
    {
        bitsallocated = 32;
        bitsstored = 32;
        pixelSize = 4;
    }
    else if (wordtype == "_16BIT_SGN_INT")
    {
        bitsallocated = 16;
        bitsstored = 16;
        pixelSize = 2;
    }
    else if (wordtype == "_8BIT_UNSGN_INT")
    {
        pixelrepresentation = 0;
        bitsallocated = 8;
        bitsstored = 8;
        pixelSize = 1;
    }
    else if (wordtype == "_32BIT_FLOAT")
    {
        // TODO
    }
    else
    {
        throw DicomifierException("Unknown VisuCoreWordType");
    }
    
    if (byteorder == "bigEndian")
    {
        highbit = 0;
    }
    else // if (byteorder == "littleEndian")
    {
        highbit = bitsallocated - 1;
    }
}

BrukerDataset* 
BrukerDirectory
::get_brukerDataset(std::string const& seriesnumber)
{
    std::string seriesnum(seriesnumber);
    // check value
    if (seriesnum.length() == 6)
    {
        seriesnum = "0" + seriesnum.substr(2,4);
    }
    
    auto it = _BrukerDatasetList.find(seriesnum);
    if (it != _BrukerDatasetList.end())
    {
        return (*it).second;
    }
    
    return NULL;
}

} // namespace bruker

} // namespace dicomifier
