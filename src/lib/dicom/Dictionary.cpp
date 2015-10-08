/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Dictionary.h"
 
namespace dicomifier
{
    
Dictionary::Dictionary(): _privateGroup(0)
{
    // Nothing to do
}

Dictionary::~Dictionary()
{
    // todo delete DcmDictEntry
}

void 
Dictionary
::AddDictEntry(const DcmDictEntry* entry)
{
    std::string keyword(entry->getTagName());
    
    std::stringstream streamgroup;
    streamgroup << std::hex << entry->getGroup();
    std::string group = streamgroup.str();
    while (group.length() != 4)
    {
        group = "0" + group;
    }
    
    std::stringstream streamelement;
    streamelement << std::hex << entry->getElement();
    std::string element = streamelement.str();
    while (element.length() != 4)
    {
        element = "0" + element;
    }
    
    std::string tagkey = group + "," + element;
    
    DcmDictEntry* dictentry = new DcmDictEntry(*entry);
    
    this->AddDictEntry(dictentry, keyword, tagkey);
}

void 
Dictionary
::AddDictEntry(DcmDictEntry* entry, std::string const & keyword, 
               std::string const & tagkey)
{
    // Warning : keyword is unique
    this->_mapKeyword.insert(std::pair<std::string, DcmDictEntry*>(keyword, entry));
    this->_mapTagKey.insert(std::pair<std::string, DcmDictEntry*>(tagkey, entry));
    
    if (entry->getPrivateCreator() != NULL)
    {
        this->_privateGroup = entry->getGroup();
    }
}

bool 
Dictionary
::IsDictEntryFromName(std::string const & name) const
{
    return this->_mapKeyword.find(name) != this->_mapKeyword.end();
}

bool 
Dictionary
::IsDictEntryFromKey(std::string const & key) const
{
    return this->_mapTagKey.find(key) != this->_mapTagKey.end();
}

DcmDictEntry* 
Dictionary
::GetEntryFromName(std::string const & name)
{
    if (this->_mapKeyword.find(name) == this->_mapKeyword.end())
    {
        throw DicomifierException("Unknown tag : " + name);
    }
    return this->_mapKeyword[name];
}
    
DcmDictEntry* 
Dictionary
::GetEntryFromKey(std::string const & key)
{
    if (this->_mapTagKey.find(key) == this->_mapTagKey.end())
    {
        throw DicomifierException("Unknown tag : " + key);
    }
    return this->_mapTagKey[key];
}

}
