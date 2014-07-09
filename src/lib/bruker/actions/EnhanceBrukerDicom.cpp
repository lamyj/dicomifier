/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/BrukerDirectory.h"
#include "core/DicomifierException.h"
#include "EnhanceBrukerDicom.h"

namespace dicomifier
{
    
namespace actions
{
    
EnhanceBrukerDicom::EnhanceBrukerDicom():
    _dataset(NULL), _brukerDir("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(DcmDataset * dataset, std::string brukerDir):
    _dataset(dataset), _brukerDir(brukerDir)
{
    // Nothing to do
}

EnhanceBrukerDicom::~EnhanceBrukerDicom()
{
    // Nothing to do
}

DcmDataset * 
EnhanceBrukerDicom
::get_dataset() const
{
    return this->_dataset;
}

void 
EnhanceBrukerDicom
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

std::string const & 
EnhanceBrukerDicom
::get_brukerDir() const
{
    return this->_brukerDir;
}

void 
EnhanceBrukerDicom
::set_brukerDir(std::string const & brukerDir)
{
    this->_brukerDir = brukerDir;
}

void 
EnhanceBrukerDicom
::run() const
{
    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(this->_brukerDir) )
    {
        throw DicomifierException("Input not a Directory: " + this->_brukerDir);
    }
    
    dicomifier::bruker::BrukerDirectory* brukerdirectory = new dicomifier::bruker::BrukerDirectory();
    
    // Parse input bruker directory
    brukerdirectory->CreateMap(this->_brukerDir);
    
    dicomifier::Rule::Pointer rules = brukerdirectory->GenerateDICOMRules(this->_dataset);
    
    rules->Execute();
    
    delete brukerdirectory;
}
    
} // namespace actions

} // namespace dicomifier
