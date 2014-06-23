#ifndef BRUKER2DICOM_H
#define BRUKER2DICOM_H
/*! \file Bruker2Dicom.h
*/

#include <string>

#include "BrukerDirectory.h"

namespace router
{

/**
 * \class Bruker2Dicom
 * \brief This class is a Brucker File converter to DICOM
 */
class creaBruker_ICUBE_EXPORT  Bruker2Dicom 
{
public:
    /**
     * Constructor
     */
    Bruker2Dicom();
    
    /**
     * Destructor
     */
    virtual ~Bruker2Dicom();

    inline void SetInputDirectory (std::string const &i) 
            { InputDirName   = i;}
            
    inline std::string GetInputDirectory() const
            { return InputDirName; }
            
    inline void SetOutputDirectory(std::string const &o) 
            { OutputDirName  = o;}
            
    inline std::string GetOutputDirectory() const
            { return OutputDirName; }
            
    /**
     * Create OutputDirName directory and 
     * read all in InputDirName directory
     */
    bool Execute();
    
    /**
     * Set attribut InputDirName and OutputDirName 
     * and then call Execute()
     * @param inputdir : input directory name
     * @param outputdir : output directory name
     */
    bool Execute(std::string const & inputdir, 
                 std::string const & outputdir);
    
protected:

private:
    /**
     * Map of bruker Dataset
     */
    BrukerDirectory* _brukerDirectory;
    
    /**
     * input directory name
     */
    std::string InputDirName;
    
    /**
     * output directory name
     */
    std::string OutputDirName;
    
};

} // namespace router

#endif
