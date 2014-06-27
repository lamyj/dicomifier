/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ceda42cb_0295_4528_9196_a427b22fd568
#define _ceda42cb_0295_4528_9196_a427b22fd568
/*! \file Bruker2Dicom.h
*/

#include <string>

#include "BrukerDirectory.h"

namespace dicomifier
{

/**
 * \class Bruker2Dicom
 * \brief This class is a Brucker File converter to DICOM
 */
class Bruker2Dicom 
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

} // namespace dicomifier

#endif // _ceda42cb_0295_4528_9196_a427b22fd568
