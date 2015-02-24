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
    /// Create an instance of BrukerDirectory
    BrukerDirectory();
    
    /// Destroy this instance of BrukerDirectory
    virtual ~BrukerDirectory();
    
    /**
     * @brief CreateMap: Parse the given directory and create datasets list
     * @param inputDir: Path of directory
     * @return number of created datasets
     */
    int CreateMap(std::string const & inputDir);
    
    /**
     * @brief get_brukerDataset: return a dataset identify by SeriesNumber field
     * @param seriesnumber: SeriesNumber of searched dataset
     * @return dataset
     */
    BrukerDataset* get_brukerDataset(std::string const& seriesnumber);

    /**
     * @brief ParseDirectory: Read recursivly a given directory and parse Bruker files
     * @param bdataset: dataset containing parsing results
     * @param inputDir: directory to read
     */
    void ParseDirectory(BrukerDataset * bdataset, std::string const & inputDir);

protected:
    /**
     * @brief isFileToRead: Look if a given file name is in FilesToRead list
     * @param file: file to test
     * @return true if file is in FilesToRead list, false otherwise
     */
    bool isFileToRead(std::string const & file);
    
    /**
     * @brief isDirToParse: identify if directory could be parsed
     * @param dir: Name of directory
     * @return true if could be parsed, false otherwise
     */
    bool isDirToParse(std::string const & dir);
    
    /**
     * @brief ParseSeriesDirectory: Parse directory containing a serie
     * @param bdataset: dataset containing parsing results
     * @param inputDir: directory to parse
     * @param StudyNumber: Number of the study
     */
    void ParseSeriesDirectory(BrukerDataset * bdataset,
                              std::string const & inputDir,
                              std::string const & StudyNumber);
    
    /**
     * @brief ParseReconstructionDirectory: Parse directory containing a reconstruction
     * @param bdataset: dataset containing parsing results
     * @param inputDir: directory to parse
     * @param StudyNumber: Number of the study
     */
    void ParseReconstructionDirectory(BrukerDataset * bdataset,
                                      std::string const & inputDir,
                                      std::string const & StudyNumber);

private:
    /// List of datasets
    BrukerMapDirectory _BrukerDatasetList;

    /// Name of files to parse
    std::vector<std::string> FilesToRead;

};

} // namespace bruker

} // namespace dicomifier

#endif // _cb9cda38_bd32_4915_8b3e_e9b01c16497d
