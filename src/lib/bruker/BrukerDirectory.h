/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _cb9cda38_bd32_4915_8b3e_e9b01c16497d
#define _cb9cda38_bd32_4915_8b3e_e9b01c16497d
/*! \file BrukerDirectory.h
*/

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "BrukerDataset.h"
#include "core/Rule.h"

// file separator
#if defined(_WIN32)
#define VALID_FILE_SEPARATOR "\\"
#define INVALID_FILE_SEPARATOR "/"
#else
#define INVALID_FILE_SEPARATOR "\\"
#define VALID_FILE_SEPARATOR "/"
#endif

namespace dicomifier
{
    
namespace bruker
{
    
/*! \class  BrukerDirectory
    \brief This class purpose is to contains hierarchy of bruker dataset
*/
class BrukerDirectory
{
    typedef std::map<std::string, BrukerDataset*> BrukerMapDirectory;
    
public:
    /**
     * Constructor
     */
    BrukerDirectory();
    
    /**
     * Destructor
     */
    virtual ~BrukerDirectory();
    
    int CreateMap(std::string const & inputDir);
    
    BrukerDataset* get_brukerDataset(std::string const& seriesnumber);
    
    /**
     * Read recursivly a given directory and parse Bruker files
     * @param inputDir : Directory to read
     */
    void ParseDirectory(BrukerDataset * bdataset, std::string const & inputDir);
    
    dicomifier::Rule::Pointer GenerateDICOMRules(DcmDataset * dataset);
    
    void getImhDataType(BrukerFieldData::Pointer const bDPT, int & pixelSize);

protected:
    /**
     * Look if a given file name is in FilesToRead list
     * @param file : file to test
     * @return true if file is in FilesToRead list, false otherwise
     */
    bool isFileToRead(std::string const & file);
    
    bool isDirToParse(std::string const & dir);
    
    void ParseStudiesDirectory(BrukerDataset * bdataset, std::string const & inputDir, std::string const & StudyNumber);
    
    void ParseSeriesDirectory(BrukerDataset * bdataset, std::string const & inputDir, std::string const & StudyNumber);

private:
    BrukerMapDirectory _BrukerDatasetList;

    std::vector<std::string> FilesToRead;

};

} // namespace bruker

} // namespace dicomifier

#endif // _cb9cda38_bd32_4915_8b3e_e9b01c16497d
