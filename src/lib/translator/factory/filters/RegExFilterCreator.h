/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _21eceffd_1f4a_4687_bae0_d84a63469d82
#define _21eceffd_1f4a_4687_bae0_d84a63469d82

#include "translator/filters/RegExFilter.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The RegExFilterCreator class
 */
class RegExFilterCreator : public TranslationCreatorBase
{
public:
    typedef RegExFilterCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of RegExFilterCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of RegExFilterCreator
    virtual ~RegExFilterCreator();

    /**
     * @brief Create Pointer to class RegExFilter
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new RegExFilter
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return RegExFilter
     */
    static std::string get_class_name() { return "RegExFilter"; }
    
protected:
    /// Create an instance of RegExFilterCreator
    RegExFilterCreator();

private:
    RegExFilterCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorRegExFilterCreator
    {
        std::string expression;
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer regexfilter;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _21eceffd_1f4a_4687_bae0_d84a63469d82
