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
    
/**
 * @brief The Dictionaries class
 */
class Dictionaries
{
public:
    /**
     * @brief get_instance: retrieve or create Dictionaries instance
     * @return the unique Dictionaries instance
     */
    static Dictionaries & get_instance();
    
    /**
     * @brief delete_instance: Destroy the Dictionaries instance
     */
    static void delete_instance();
    
    /// Destructor.
    virtual ~Dictionaries();
    
    /**
     * @brief ParsePrivateDictionary: Parse and add the given Private Dictionary
     * @param filename: path to the dictionary XML file
     */
    void ParsePrivateDictionary(std::string const & filename);
    
    /**
     * @brief GetTagFromName: Get the DcmTag for a given entry
     * @param name: name of the searched entry
     * @param dict: name of the dictionary
     * @param finalypublic: (out) indicate if the entry is find in the public or private Dictionary
     * @return DcmTag of the entry
     */
    DcmTag GetTagFromName(std::string const & name, std::string const & dict, bool & finalypublic);

    /**
     * @brief GetTagFromKey: Get the DcmTag for a given entry
     * @param key: tag of the searched entry
     * @param dict: name of the Dictionary
     * @param finalypublic: (out) indicate if the entry is find in the public or private Dictionary
     * @return DcmTag of the entry
     */
    DcmTag GetTagFromKey(std::string const & key, std::string const & dict, bool & finalypublic);
    
    /**
     * @brief FindCreatorElementNumber: Return the number of a given private creator
     * @param privatecreator: Private creator name
     * @param dataset: dataset containing the private creator
     * @return number of the private creator
     */
    Uint16 FindCreatorElementNumber(std::string const & privatecreator, 
                                    DcmDataset* dataset = NULL);

    static std::string public_dictionary_as_json();

protected:
    /**
     * @brief AddPublicDictionary: add the DCMTK public Dictionary
     */
    void AddPublicDictionary();

private:
    /// Unique instance of Dictionaries
    static Dictionaries* _instance;
    
    /// Create a new instance of Dictionaries
    Dictionaries();
    
    /// List of all registered dictionaries
    std::map<std::string, Dictionary::Pointer> _dictionaries;

    // Purposely not implemented
    Dictionaries(Dictionaries const & other);
    void operator=(Dictionaries const & other);

};

} // namespace dicomifier

#endif // _1f267fee_1346_42ed_a64f_0c4f2fe7c36d
