#include "Bruker2Dicom.h"

namespace dicomifier
{

Bruker2Dicom::Bruker2Dicom():
    _brukerDirectory(NULL),
    InputDirName(""),
    OutputDirName("")
{
    _brukerDirectory = new BrukerDirectory();
}

Bruker2Dicom::~Bruker2Dicom()
{
    if (_brukerDirectory != NULL)
    {
        delete _brukerDirectory;
        _brukerDirectory = NULL;
    }
}

bool Bruker2Dicom::Execute()
{    
    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(this->InputDirName) )
    {
        std::cout << "KO : [" << this->InputDirName 
                  << "] is not a Directory." << std::endl;
        throw (BrukerHopelessException ("Input not a Directory"));
    }

    // ----- Check output directory name -----
    if ( ! boost::filesystem::is_directory(this->OutputDirName) )
    {
        bool res = BrukerDirectory::CreateDirectory(this->OutputDirName);
        if (!res) 
        {
            std::cout << "[" << this->OutputDirName 
                      << "] Directory creation failure " << std::endl;
            throw (BrukerHopelessException ("Output directory creation failure "));
        }
    }
    
    // Parse input directory
    _brukerDirectory->CreateMap(this->InputDirName);
    
    _brukerDirectory->GenerateDICOMRules(this->OutputDirName);
    
    return true;
}

bool Bruker2Dicom::Execute(std::string const & inputdir, 
                           std::string const & outputdir)
{
    // Set directory name
    if (inputdir != "")
    {
        this->SetInputDirectory(inputdir);
    }
    if (outputdir != "")
    {
        this->SetOutputDirectory(outputdir);
    }
    
    // call Execute
    return Execute();
}

} // namespace dicomifier
