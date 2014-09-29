/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1f267fee_1346_42ed_a64f_0c4f2fe7c36d
#define _1f267fee_1346_42ed_a64f_0c4f2fe7c36d

#include "dicom/Dictionary.h"

namespace dicomifier
{
    
class Dictionaries
{
public:
    static Dictionaries & get_instance();
    
    virtual ~Dictionaries();
    
    void ParsePrivateDictionary(std::string const & filename);
    
    DcmTag GetTagFromName(std::string const & name, std::string const & dict, bool & finalypublic);
    DcmTag GetTagFromKey(std::string const & key, std::string const & dict, bool & finalypublic);
    
    Uint16 FindCreatorElementNumber(std::string const & privatecreator, 
                                    DcmDataset* dataset = NULL);

protected:
    void AddPublicDictionary();

private:
    static Dictionaries* _instance;
    
    Dictionaries();
    
    std::map<std::string, Dictionary::Pointer> _dictionaries;

    // Purposely not implemented
    Dictionaries(Dictionaries const & other);
    void operator=(Dictionaries const & other);

};

} // namespace dicomifier

#endif // _1f267fee_1346_42ed_a64f_0c4f2fe7c36d
