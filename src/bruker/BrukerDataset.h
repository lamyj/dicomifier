/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1f35fffc_e764_42fe_883b_6aa220e3d65c
#define _1f35fffc_e764_42fe_883b_6aa220e3d65c
/*! \file BrukerDataset.h
*/

#include <string>
#include <fstream>

#include "BrukerFieldData.h"
    
namespace dicomifier
{
    
/*! \class  BrukerDataset
    \brief This class purpose is to extract information from a bruker experiment and setup the extracted information for an easy use
*/
class BrukerDataset
{
    typedef std::map<std::string, BrukerFieldData> BrukerMapType;
    
public:
    /**
     * Constructor
     */
	BrukerDataset();
    
    /**
     * Copy Constructor
     */
    BrukerDataset(BrukerDataset const & dataset);
    
    /**
     * Destructor
     */
	virtual ~BrukerDataset();
    
    /**
     * Read (and parse) a given file
     * @param FileToRead : file path
     * @return : true if read is succeful, false otherwise
     */
	bool LoadFile(std::string FileToRead);
    
    /**
     * Parse a given string
     * @param data : string to parse
     */
    void Parse(std::string const & data);
    
    /**
     * Parse a given stream buffer
     * @param streamdata : buffer to parse
     */
    void Parse(std::istream & streamdata);
    
    /**
     * Return this as string. (Only used to debug)
     * @return this as string
     */
    std::string toString() const;
    
    /**
     * Modify values for a given key
     * @param key : search key
     * @param value : new value
     */
    void SetFieldData(std::string const & key, 
                      BrukerFieldData const & value);
    
    /**
     * Return values for a given key
     * @param key : search key
     * @return values
     */
    BrukerFieldData GetFieldData(std::string key) const;
    
    /**
     * @return : true if dataset contains key, false otherwise
     */
    bool HasFieldData(std::string key) const;

protected:

private:
    /**
     * Contains all BrukerDataset elements
     */
    BrukerMapType BrukerHeaderMap;
};

} // namespace dicomifier

#endif // _1f35fffc_e764_42fe_883b_6aa220e3d65c
