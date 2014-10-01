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
    
class Dictionary
{
public:
    typedef Dictionary Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~Dictionary();
    
    void AddDictEntry(const DcmDictEntry* entry);
    void AddDictEntry(DcmDictEntry* entry, std::string const & keyword, 
                      std::string const & tagkey);
                      
    bool IsDictEntryFromName(std::string const & name) const;
    bool IsDictEntryFromKey(std::string const & key) const;
                      
    DcmDictEntry* GetEntryFromName(std::string const & name);
    DcmDictEntry* GetEntryFromKey(std::string const & key);
    
    Uint16 get_privateGroup() const { return this->_privateGroup; }
    void set_privateGroup(Uint16 const & group) { this->_privateGroup = group; }

protected:
    Dictionary();

private:
    std::map<std::string, DcmDictEntry*> _mapKeyword;
    std::map<std::string, DcmDictEntry*> _mapTagKey;
    
    Uint16 _privateGroup;
    
    Dictionary(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace dicomifier

#endif // _b07e6f12_6133_4d6d_b168_f556cf892634
