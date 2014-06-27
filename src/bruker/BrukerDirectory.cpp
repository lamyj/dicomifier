#include "BrukerDirectory.h"
#include "RulesDocument.h"

namespace router
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

void BrukerDirectory::CreateMap(std::string const & inputDir)
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
            if (isFileToRead((*it).filename()))
            {// yes
                // Parse file
                std::string file = inputDir + VALID_FILE_SEPARATOR + (*it).filename();
                mainDataset->LoadFile(file);
            }
        }
        // Else element is a directory
        else
        {
            subDirectoryName.push_back((*it).filename());
        }
    }
    
    if (subDirectoryName.size() != 0)
    {
        std::vector<std::string>::iterator iter = subDirectoryName.begin();
        for (; iter != subDirectoryName.end(); ++iter)
        {
            BrukerDataset * dataset = new BrukerDataset(*mainDataset);
            
            std::string file = inputDir + VALID_FILE_SEPARATOR + (*iter);
                    
            this->ParseDirectory(dataset, file);
            
            this->_BrukerDatasetList[ (*iter) ] = dataset;
        }
        delete mainDataset;
    }
    else
    {
        this->_BrukerDatasetList[ "main" ] = mainDataset;
    }
}

void BrukerDirectory::ParseDirectory(BrukerDataset * bdataset, std::string const & inputDir)
{
    if (bdataset == NULL)
    {
        return;
    }
    
    //std::cout << bdataset->toString() << std::endl;
    
    // scan inputDir
    boost::filesystem::directory_iterator iter(inputDir), it_end;
    for(; iter != it_end; ++iter)
    {
        // If element is a file
        if(! boost::filesystem::is_directory( (*iter) ) )
        {
            // Should we parse this file ?
            if (isFileToRead((*iter).filename()))
            {// yes
                std::string file = inputDir + VALID_FILE_SEPARATOR + (*iter).filename();
                // Parse file
                bdataset->LoadFile(file);
            }
        }
        // Else element is a directory
        else
        {
            // recursively scan directory
            std::string subdir = inputDir + VALID_FILE_SEPARATOR + (*iter).filename();
            ParseDirectory(bdataset, subdir);
        }
    }
}

bool BrukerDirectory::CreateDirectory(std::string const & OutputDir)
{
    std::string systemCommand;

    boost::filesystem::directory_entry ent(OutputDir);
    if ( ! boost::filesystem::is_directory(ent) )    // dirout not found
    {
        systemCommand = "mkdir " + OutputDir;        // create it!      
        system (systemCommand.c_str());
    }
    
    // Return true if directory exist (creation done), false otherwise
    return boost::filesystem::is_directory(ent);
}

bool BrukerDirectory::isFileToRead(std::string const & file)
{
    return std::find(FilesToRead.begin(), 
                     FilesToRead.end(), file) != FilesToRead.end();
}

void BrukerDirectory::getImhDataType(BrukerFieldData const & bDPT, int & pixelSize)
{
    if(bDPT.GetDataType() == "string")
    {         
        std::string brukerDataPixelType = bDPT.GetStringValue()[0];

        if (brukerDataPixelType ==  "ip_short") 
        {
            pixelSize = 2;
        }
        if (brukerDataPixelType ==  "ip_int") 
        {
            pixelSize = 4;
        }
        if (brukerDataPixelType ==  "ip_char") 
        {
            pixelSize = 1;
        }
    }
    else
    {
        int brukerDataPixelType = bDPT.GetIntValue()[0];

        if (brukerDataPixelType ==  2) 
        {
            pixelSize = 2;
        }
        if (brukerDataPixelType ==  3) 
        {
            pixelSize = 2;
        }    
        if (brukerDataPixelType ==  1) 
        {
            pixelSize = 1;
        }     
    }
}

void BrukerDirectory::GenerateDICOMRules(std::string const & outputdir)
{
    int count = 0;
    BrukerMapDirectory::iterator it = _BrukerDatasetList.begin();
    for (; it != _BrukerDatasetList.end(); ++it)
    {
        std::string xmlfilename = (*it).first;
        xmlfilename = "Rules_" + xmlfilename + ".xml";
        
        RulesDocument rdoc;
        
        // Columns                      0x0028,0x0011
        rdoc.AddAction(AT_Set_Element, "Columns", 
                       (*it).second->GetFieldData("IM_SIX"), EVR_US);
        
        // Rows                         0x0028,0x0010
        rdoc.AddAction(AT_Set_Element, "Rows",
                       (*it).second->GetFieldData("IM_SIY"), EVR_US);
                       
        // Number of Frames             0x0028,0x0008
        rdoc.AddAction(AT_Set_Element, "Number of Frames",
                       (*it).second->GetFieldData("IM_SIZ"), EVR_IS);
                       
        int pixelSize;
        getImhDataType((*it).second->GetFieldData("DATTYPE"), pixelSize);
        
        // Bits allocated               0x0028,0x0100
        rdoc.AddAction(AT_Set_Element, "Bits Allocated",
                       BrukerFieldData(pixelSize * 8), EVR_US);

        // Bits stored                  0x0028,0x0101
        rdoc.AddAction(AT_Set_Element, "Bits Stored",
                       BrukerFieldData(pixelSize * 8), EVR_US);

        // High Bit                     0x0028,0x0102
        rdoc.AddAction(AT_Set_Element, "High Bit",
                       BrukerFieldData(pixelSize * 8 - 1), EVR_US);

        // pixel representation         0x0028,0x0103
        rdoc.AddAction(AT_Set_Element, "Pixel Representation",
                       BrukerFieldData("1"), EVR_US);

        // sample per pixel             0x0028,0x0002
        rdoc.AddAction(AT_Set_Element, "Samples per Pixel",
                       BrukerFieldData("1"), EVR_US);
                       
        // Slice Thickness              0x0018,0x0050
        rdoc.AddAction(AT_Set_Element, "Slice Thickness",
                       (*it).second->GetFieldData("PVM_SPackArrSliceDistance"), EVR_DS);

        // Series Number                0x0020,0x0011
        rdoc.AddAction(AT_Set_Element, "Series Number",
                       BrukerFieldData("0"), EVR_IS);

        // Instance Number              0x0020,0x0013
        rdoc.AddAction(AT_Set_Element, "Instance Number",
                       BrukerFieldData(++count), EVR_IS);
                       
        // Patient Name                 0x0010,0x0010
        rdoc.AddAction(AT_Set_Element, "Patient Name",
                       (*it).second->GetFieldData("SUBJECT_name_string"), EVR_PN,
                       true);

        // Patient's ID                 0x0010,0x0020
        rdoc.AddAction(AT_Set_Element, "Patient ID",
                       (*it).second->GetFieldData("SUBJECT_name_string"), EVR_LO,
                       true);
                       
        char uidstudy[128];
        dcmGenerateUniqueIdentifier(uidstudy, SITE_STUDY_UID_ROOT);

        // Study Instance UID           0x0020,0x000d
        rdoc.AddAction(AT_Set_Element, "Study Instance UID",
                       BrukerFieldData(std::string(uidstudy)), EVR_UI);
                       
        char uidseries[128];
        dcmGenerateUniqueIdentifier(uidseries, SITE_SERIES_UID_ROOT);

        // Series Instance UID          0x0020,0x000e
        rdoc.AddAction(AT_Set_Element, "Series Instance UID",
                       BrukerFieldData(std::string(uidseries)), EVR_UI);

        std::string datetime = (*it).second->GetFieldData("SUBJECT_date").GetValueToString(true);

        // Study Date                   0x0008,0x0020
        rdoc.AddAction(AT_Set_Element, "Study Date",
                       BrukerFieldData(datetime.substr(9,11)), EVR_DA);

        // Study Time                   0x0008,0x0030
        rdoc.AddAction(AT_Set_Element, "Study Time",
                       BrukerFieldData(datetime.substr(0,8)), EVR_TM);

        // Study Description            0x0008,0x1030
        rdoc.AddAction(AT_Set_Element, "Study Description",
                       (*it).second->GetFieldData("SUBJECT_study_name"), EVR_LO,
                       true);

        std::string strSerieDescr = (*it).first + "." +
                                    (*it).second->GetFieldData("ACQ_scan_name").GetValueToString(true) + "." +
                                    (*it).second->GetFieldData("ACQ_method").GetValueToString(true);
                                    
        // Series Description           0x0008,0x103e
        rdoc.AddAction(AT_Set_Element, "Series Description",
                       BrukerFieldData(strSerieDescr), EVR_LO);

        // Modality                     0x0008,0x0060
        rdoc.AddAction(AT_Set_Element, "Modality",
                       BrukerFieldData("MR"), EVR_CS);
                       
        // Image Orientation Patient    0x0020,0x0037
        /*rdoc.AddAction(AT_Set_Element, "Image Orientation (Patient)",
                       , EVR_DS); 
        TODO look how to get this information*/

        // Image Position Patient    0x0020,0x0032
        /*rdoc.AddAction(AT_Set_Element, "Image Position (Patient)",
                       , EVR_DS); 
        TODO look how to get this information*/

        /* 
        
        std::string method = (*it).second->GetFieldData("Method").GetValueToString(true);
        
        // Private dictionary
        if (method == "DtiEpi" || method == "DtiStandard")
        {
            //0x0029,0x0101
            rdoc.AddAction(AT_Set_Element, "0x0029,0x0101", 
                           (*it).second->GetFieldData("PVM_DwNDiffDir"), EVR_US);

            //0x0029,0x0102
            rdoc.AddAction(AT_Set_Element, "0x0029,0x0102", 
                           (*it).second->GetFieldData("PVM_DwNDiffExpEach"), EVR_US);

            //0x0029,0x0103
            rdoc.AddAction(AT_Set_Element, "0x0029,0x0103", 
                           (*it).second->GetFieldData("PVM_DwAoImages"), EVR_US);
        
            //0x0029,0x0104
            rdoc.AddAction(AT_Set_Element, "0x0029,0x0104", 
                           (*it).second->GetFieldData("PVM_DwBvalEach"), EVR_DS);
        }*/
        
        std::string rdocfile = outputdir + VALID_FILE_SEPARATOR + xmlfilename;
        rdoc.WriteDocument(rdocfile);
    }
}

} // namespace router
