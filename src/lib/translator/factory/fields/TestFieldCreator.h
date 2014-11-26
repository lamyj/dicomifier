/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7d732393_65e2_422d_a940_942d23ed42bb
#define _7d732393_65e2_422d_a940_942d23ed42bb

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{

/**
 * @brief The TestFieldCreator class
 */
class TestFieldCreator : public TranslationCreatorBase
{
public:
    typedef TestFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of TestFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of TestFieldCreator
    virtual ~TestFieldCreator();

    /**
     * @brief Create Pointer to class TestField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new TestField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return TestField
     */
    static std::string get_class_name() { return "TestField"; }

protected:
    /// Create an instance of TestFieldCreator
    TestFieldCreator();

private:
    TestFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _7d732393_65e2_422d_a940_942d23ed42bb
