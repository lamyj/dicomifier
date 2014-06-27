#ifndef _cb9cda38_bd32_4915_8b3e_e9b01c16497d
#define _cb9cda38_bd32_4915_8b3e_e9b01c16497d
/*! \file BrukerDirectory.h
*/

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "BrukerDataset.h"
#include "BrukerException.h"

// file separator
#if defined(_WIN32)
#define VALID_FILE_SEPARATOR "\\"
#define INVALID_FILE_SEPARATOR "/"
#else
#define INVALID_FILE_SEPARATOR "\\"
#define VALID_FILE_SEPARATOR "/"
#endif

namespace router
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
    
    void CreateMap(std::string const & inputDir);
    
    /**
     * Read recursivly a given directory and parse Bruker files
     * @param inputDir : Directory to read
     */
    void ParseDirectory(BrukerDataset * bdataset, std::string const & inputDir);
    
    /**
     * Create a directory
     * @param OutputDir : Directory name to create
     * @return true if directory creation is succeful, false otherwise
     */
    static bool CreateDirectory(std::string const & OutputDir);
    
    void GenerateDICOMRules(std::string const & outputdir);

protected:
    /**
     * Look if a given file name is in FilesToRead list
     * @param file : file to test
     * @return true if file is in FilesToRead list, false otherwise
     */
    bool isFileToRead(std::string const & file);
    
    void getImhDataType(BrukerFieldData const & bDPT, int & pixelSize);

private:
    BrukerMapDirectory _BrukerDatasetList;

    std::vector<std::string> FilesToRead;

};

} // namespace router

#endif // _cb9cda38_bd32_4915_8b3e_e9b01c16497d
