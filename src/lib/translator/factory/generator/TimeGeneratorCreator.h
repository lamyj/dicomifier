/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _64051fb6_5e20_447d_9d76_4e0fcb7b7863
#define _64051fb6_5e20_447d_9d76_4e0fcb7b7863

#include "translator/generator/TimeGenerator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The TimeGeneratorCreator class
 */
class TimeGeneratorCreator : public TranslationCreatorBase
{
public:
    typedef TimeGeneratorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of TimeGeneratorCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of TimeGeneratorCreator
    virtual ~TimeGeneratorCreator();

    /**
     * @brief Create Pointer to class TimeGenerator
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new TimeGenerator
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return TimeGenerator
     */
    static std::string get_class_name() { return "TimeGenerator"; }
    
protected:
    /// Create an instance of TimeGeneratorCreator
    TimeGeneratorCreator();

private:
    TimeGeneratorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorTimeGeneratorCreator
    {
        mutable dicomifier::translator::Tag::Pointer timegenerator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _64051fb6_5e20_447d_9d76_4e0fcb7b7863


