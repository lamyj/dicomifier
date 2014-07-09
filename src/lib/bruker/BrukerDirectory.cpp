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
            subDirectoryName.push_back((*it).path().filename().c_str());
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

dicomifier::Rule::Pointer BrukerDirectory::GenerateDICOMRules(DcmDataset * dataset)
{
    // Search SeriesNumber dicom element
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SeriesNumber, str);
    if (cond.bad())
    {
        throw dicomifier::DicomifierException("Error: Can't read SeriesNumber attribut, error = " + 
                                              std::string(cond.text()));
    }
    
    auto rule = dicomifier::Rule::New();
    
    int count = 0;
    //auto it = _BrukerDatasetList.find(std::string(str.c_str()));
    auto it = _BrukerDatasetList.find("pdata");
    if (it != _BrukerDatasetList.end())
    {
        // Columns                      0x0028,0x0011
        if ((*it).second->HasFieldData("IM_SIX"))
        {
            auto action = dicomifier::actions::SetElement<EVR_US>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_Columns);
            
            dicomifier::actions::SetElement<EVR_US>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("IM_SIX").GetIntValue())
            {
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_US>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
        
        // Rows                         0x0028,0x0010
        if ((*it).second->HasFieldData("IM_SIY"))
        {
            auto action = dicomifier::actions::SetElement<EVR_US>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_Rows);
            
            dicomifier::actions::SetElement<EVR_US>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("IM_SIY").GetIntValue())
            {
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_US>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
                       
        // Number of Frames             0x0028,0x0008
        if ((*it).second->HasFieldData("IM_SIZ"))
        {
            auto action = dicomifier::actions::SetElement<EVR_IS>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_NumberOfFrames);
            
            dicomifier::actions::SetElement<EVR_IS>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("IM_SIZ").GetIntValue())
            {
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_IS>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
                       
        if ((*it).second->HasFieldData("DATTYPE"))
        {
            int pixelSize;
            getImhDataType((*it).second->GetFieldData("DATTYPE"), pixelSize);
        
            // Bits allocated               0x0028,0x0100
            {
                auto action = dicomifier::actions::SetElement<EVR_US>::New();
                action->set_dataset(dataset);
                action->set_tag(DCM_BitsAllocated);
                action->set_value(pixelSize * 8);
                
                rule->add_action(action);
            }

            // Bits stored                  0x0028,0x0101
            {
                auto action = dicomifier::actions::SetElement<EVR_US>::New();
                action->set_dataset(dataset);
                action->set_tag(DCM_BitsStored);
                action->set_value(pixelSize * 8);
                
                rule->add_action(action);
            }

            // High Bit                     0x0028,0x0102
            {
                auto action = dicomifier::actions::SetElement<EVR_US>::New();
                action->set_dataset(dataset);
                action->set_tag(DCM_HighBit);
                action->set_value(pixelSize * 8);
                
                rule->add_action(action);
            }
        }

        // pixel representation         0x0028,0x0103
        {
            auto action = dicomifier::actions::SetElement<EVR_US>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_PixelRepresentation);
            action->set_value(1);
            
            rule->add_action(action);
        }

        // sample per pixel             0x0028,0x0002
        {
            auto action = dicomifier::actions::SetElement<EVR_US>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_SamplesPerPixel);
            action->set_value(1);
            
            rule->add_action(action);
        }
                       
        // Slice Thickness              0x0018,0x0050
        if ((*it).second->HasFieldData("PVM_SPackArrSliceDistance"))
        {
            auto action = dicomifier::actions::SetElement<EVR_DS>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_SliceThickness);
            
            dicomifier::actions::SetElement<EVR_DS>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("PVM_SPackArrSliceDistance").GetDoubleValue())
            {
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_DS>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
        
        // Series Number                0x0020,0x0011
        {
            auto action = dicomifier::actions::SetElement<EVR_IS>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_SeriesNumber);
            action->set_value(0);
            
            rule->add_action(action);
        }

        // Instance Number              0x0020,0x0013
        {
            auto action = dicomifier::actions::SetElement<EVR_IS>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_InstanceNumber);
            action->set_value(++count);
            
            rule->add_action(action);
        }
                       
        // Patient Name                 0x0010,0x0010
        if ((*it).second->HasFieldData("SUBJECT_name_string"))
        {
            auto action = dicomifier::actions::SetElement<EVR_PN>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_PatientName);
            
            dicomifier::actions::SetElement<EVR_PN>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("SUBJECT_name_string").GetStringValue())
            {
                BrukerFieldData::CleanString(value);
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_PN>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }

        // Patient's ID                 0x0010,0x0020
        if ((*it).second->HasFieldData("SUBJECT_name_string"))
        {
            auto action = dicomifier::actions::SetElement<EVR_LO>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_PatientID);
            
            dicomifier::actions::SetElement<EVR_LO>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("SUBJECT_name_string").GetStringValue())
            {
                BrukerFieldData::CleanString(value);
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_LO>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
                       
        char uidstudy[128];
        dcmGenerateUniqueIdentifier(uidstudy, SITE_STUDY_UID_ROOT);

        // Study Instance UID           0x0020,0x000d
        {
            auto action = dicomifier::actions::SetElement<EVR_UI>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_StudyInstanceUID);
            action->set_value(OFString(uidstudy));
            
            rule->add_action(action);
        }
                       
        char uidseries[128];
        dcmGenerateUniqueIdentifier(uidseries, SITE_SERIES_UID_ROOT);

        // Series Instance UID          0x0020,0x000e
        {
            auto action = dicomifier::actions::SetElement<EVR_UI>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_SeriesInstanceUID);
            action->set_value(OFString(uidseries));
            
            rule->add_action(action);
        }

        if ((*it).second->HasFieldData("SUBJECT_date"))
        {
            std::string datetime = (*it).second->GetFieldData("SUBJECT_date").GetValueToString(true);

            // Study Date                   0x0008,0x0020
            {
                auto action = dicomifier::actions::SetElement<EVR_DA>::New();
                action->set_dataset(dataset);
                action->set_tag(DCM_StudyDate);
                
                std::string date = datetime.substr(9,11);
                action->set_value(OFString(date.c_str()));
                
                rule->add_action(action);
            }

            // Study Time                   0x0008,0x0030
            {
                auto action = dicomifier::actions::SetElement<EVR_TM>::New();
                action->set_dataset(dataset);
                action->set_tag(DCM_StudyTime);
                
                std::string time = datetime.substr(0,8);
                action->set_value(OFString(time.c_str()));
                
                rule->add_action(action);
            }
        }
        
        // Study Description            0x0008,0x1030
        if ((*it).second->HasFieldData("SUBJECT_study_name"))
        {
            auto action = dicomifier::actions::SetElement<EVR_LO>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_StudyDescription);
            
            dicomifier::actions::SetElement<EVR_LO>::ArrayType vect;
            for (auto value : (*it).second->GetFieldData("SUBJECT_study_name").GetStringValue())
            {
                BrukerFieldData::CleanString(value);
                vect.push_back(boost::lexical_cast<dicomifier::actions::SetElement<EVR_LO>::ValueType>(value));
            }
            action->set_value(vect);
            
            rule->add_action(action);
        }
        
        if ((*it).second->HasFieldData("ACQ_scan_name") && (*it).second->HasFieldData("ACQ_method"))
        {
            std::string strSerieDescr = (*it).first + "." +
                                        (*it).second->GetFieldData("ACQ_scan_name").GetValueToString(true) + "." +
                                        (*it).second->GetFieldData("ACQ_method").GetValueToString(true);
                                        
            // Series Description           0x0008,0x103e
            auto action = dicomifier::actions::SetElement<EVR_LO>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_SeriesDescription);
            action->set_value(OFString(strSerieDescr.c_str()));
            
            rule->add_action(action);
        }

        // Modality                     0x0008,0x0060
        {
            auto action = dicomifier::actions::SetElement<EVR_CS>::New();
            action->set_dataset(dataset);
            action->set_tag(DCM_Modality);
            action->set_value("MR");
            
            rule->add_action(action);
        }
                       
        // Image Orientation Patient    0x0020,0x0037
        /*rdoc.AddAction(AT_Set_Element, "Image Orientation (Patient)",
                       , EVR_DS); 
        TODO look how to get this information*/

        // Image Position Patient    0x0020,0x0032
        /*rdoc.AddAction(AT_Set_Element, "Image Position (Patient)",
                       , EVR_DS); 
        TODO look how to get this information*/
    }
    
    return rule;
}

} // namespace bruker

} // namespace dicomifier
