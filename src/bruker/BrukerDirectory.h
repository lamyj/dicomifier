#ifndef BRUKERDIRECTORY_H
#define BRUKERDIRECTORY_H
/*! \file BrukerDirectory.h
*/

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "BrukerSystem.h"
#include "BrukerException.h"
#include "BrukerDataset.h"

// file separator
#if defined(_WIN32)
#define VALID_FILE_SEPARATOR "\\"
#define INVALID_FILE_SEPARATOR "/"
#else
#define INVALID_FILE_SEPARATOR "\\"
#define VALID_FILE_SEPARATOR "/"
#endif

/*! \class  BrukerDirectory
    \brief This class purpose is to contains hierarchy of bruker dataset
*/
class creaBruker_ICUBE_EXPORT BrukerDirectory
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

#endif
