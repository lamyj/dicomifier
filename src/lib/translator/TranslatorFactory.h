/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f5d0239c_cb66_40b2_9a19_849a6c7b11db
#define _f5d0239c_cb66_40b2_9a19_849a6c7b11db

#include <functional>
#include <map>

#include "TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
/**
 * @brief Factory for generate translation to DICOM from other format
 */
class TranslatorFactory
{
public:
    /**
     * Create (if not exist) and return an unique instance of TranslatorFactory
     * @return unique instance of TranslatorFactory
     */
    static TranslatorFactory & get_instance();
    
    /// Destroy the TranslatorFactory
    virtual ~TranslatorFactory();

    /// Register creator classes
    template<typename T>
    unsigned int register_();
    
    /**
     * Look if a given class is register in this factory
     * @param class_: class name to create
     * @return true if Factory can generate given class, false otherwise
     */
    bool can_create(std::string const & class_) const;

    /**
     * Create an instance of given class
     * @param value: class name of the object to create
     * @return smart pointer to the created object
     */
    Tag::Pointer create(boost::property_tree::ptree::value_type & value,
                        DcmDataset* dataset, 
                        DcmEVR evr);
    
protected:

private:
    typedef std::function<std::shared_ptr<TranslationCreatorBase>()> TranslationCreator;
    
    /// Create an instance of TranslatorFactory
    TranslatorFactory();
    
    /// Unique Instance
    static TranslatorFactory * _instance;
    
    /// Map of managed creator
    std::map<std::string, TranslationCreator> _creators;

    // Purposely not implemented
    TranslatorFactory(TranslatorFactory const & other);
    void operator=(TranslatorFactory const & other);

};
    
} // namespace translator

} // namespace dicomifier

#include "TranslatorFactory.txx"

#endif // _f5d0239c_cb66_40b2_9a19_849a6c7b11db
