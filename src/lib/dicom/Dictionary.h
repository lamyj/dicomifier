/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _b07e6f12_6133_4d6d_b168_f556cf892634
#define _b07e6f12_6133_4d6d_b168_f556cf892634

#include <map>
#include <memory>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/DicomifierException.h"

namespace dicomifier
{

/**
 * @brief The Dictionary class: containing public or private DICOM Attributs.
 */
class Dictionary
{
public:
    typedef Dictionary Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to a new instance of Dictionary
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destructor.
    virtual ~Dictionary();
    
    /**
     * @brief AddDictEntry: insert new entry in the Dictionary
     * @param entry: entry to be insert
     */
    void AddDictEntry(const DcmDictEntry* entry);

    /**
     * @brief AddDictEntry: insert new entry in the Dictionary
     * @param entry: entry to be insert
     * @param keyword: name of the entry
     * @param tagkey: tag of the entry
     */
    void AddDictEntry(DcmDictEntry* entry, std::string const & keyword, 
                      std::string const & tagkey);
                      
    /**
     * @brief IsDictEntryFromName: look if dictionary the given key
     * @param name: name of the entry
     * @return true if key exist, false otherwise
     */
    bool IsDictEntryFromName(std::string const & name) const;

    /**
     * @brief IsDictEntryFromKey: look if dictionary the given key
     * @param key: tag of the entry
     * @return true if key exist, false otherwise
     */
    bool IsDictEntryFromKey(std::string const & key) const;
                      
    /**
     * @brief GetEntryFromName: retrieve a given entry
     * @param name: name of the searched entry
     * @return the entry if exist, throw an exception otherwise
     */
    DcmDictEntry* GetEntryFromName(std::string const & name);

    /**
     * @brief GetEntryFromKey: retrieve a given entry
     * @param key: tag key of the searched entry
     * @return the entry if exist, throw an exception otherwise
     */
    DcmDictEntry* GetEntryFromKey(std::string const & key);
    
    /**
     * @brief get_privateGroup: getter for privateGroup
     * @return privateGroup
     */
    Uint16 get_privateGroup() const { return this->_privateGroup; }

    /**
     * @brief set_privateGroup: setter for privateGroup
     * @param group: new value for privateGroup
     */
    void set_privateGroup(Uint16 const & group) { this->_privateGroup = group; }

protected:
    /// Create a new instance of Dictionary
    Dictionary();

private:
    /// List of the entries sorted by name
    std::map<std::string, DcmDictEntry*> _mapKeyword;

    /// List of the entries sorted by tag key
    std::map<std::string, DcmDictEntry*> _mapTagKey;
    
    /// Contains number for the private creator
    Uint16 _privateGroup;
    
    Dictionary(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace dicomifier

#endif // _b07e6f12_6133_4d6d_b168_f556cf892634
