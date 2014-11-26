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
#include "core/DicomifierException.h"
    
namespace dicomifier
{
    
namespace bruker
{
    
struct VISU_FRAMEGROUP_TYPE
{
    int length; // Number of frame group elements
    std::vector<std::pair<std::string, int>> groupDepVals;
} ;
    
/**
 * @brief The BrukerDataset class: This class purpose is to extract information from a bruker experiment
 *  and setup the extracted information for an easy use
 */
class BrukerDataset
{
    typedef std::map<std::string, BrukerFieldData::Pointer> BrukerMapType;
    
public:
    /// Create an instance of BrukerDataset
    BrukerDataset();
    
    /**
     * @brief BrukerDataset: Copy constructor
     * @param dataset: dataset to copy
     */
    BrukerDataset(BrukerDataset const & dataset);
    
    /// Destroy this instance of BrukerDataset
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
     * Modify values for a given key
     * @param key : search key
     * @param value : new value
     */
    void SetFieldData(std::string const & key, 
                      BrukerFieldData::Pointer const value);
    
    /**
     * Return values for a given key
     * @param key : search key
     * @return values
     */
    BrukerFieldData::Pointer GetFieldData(std::string key) const;
    
    /**
     * @return : true if dataset contains key, false otherwise
     */
    bool HasFieldData(std::string key) const;
    
    /**
     * @brief create_frameGroupLists: identify groups of images
     * @param coreframecount: (out) number of images
     * @return cardinality of each group
     */
    std::vector<int> create_frameGroupLists(int & coreframecount);
    
    /**
     * @brief get_indexForValue: get index and start position for a given group
     * @param valuename: name of group
     * @param indexposition: (out) index of the group
     * @param startposition: (out) first position for the group
     */
    void get_indexForValue(std::string const & valuename,
                           int & indexposition,
                           int & startposition) const;

protected:

private:
    /// Contains all BrukerDataset elements
    BrukerMapType BrukerHeaderMap;
    
    /// Groups of images
    std::vector<VISU_FRAMEGROUP_TYPE> _frameGroupLists;
};

} // namespace bruker

} // namespace dicomifier

#endif // _1f35fffc_e764_42fe_883b_6aa220e3d65c
