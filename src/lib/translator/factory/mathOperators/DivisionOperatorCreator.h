/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0073441a_6378_4505_b000_4be60f9faa85
#define _0073441a_6378_4505_b000_4be60f9faa85

#include "translator/mathOperators/DivisionOperator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The DivisionOperatorCreator class
 */
class DivisionOperatorCreator : public TranslationCreatorBase
{
public:
    typedef DivisionOperatorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DivisionOperatorCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of DivisionOperatorCreator
    virtual ~DivisionOperatorCreator();

    /**
     * @brief Create Pointer to class DivisionOperator
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new DivisionOperator
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return DivisionOperator
     */
    static std::string get_class_name() { return "DivisionOperator"; }

protected:
    /// Create an instance of DivisionOperatorCreator
    DivisionOperatorCreator();

private:
    DivisionOperatorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDivisionOperatorCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer divisionoperator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _0073441a_6378_4505_b000_4be60f9faa85
