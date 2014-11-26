/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _34072676_d7ea_4e61_8603_7f63d6e2ce0a
#define _34072676_d7ea_4e61_8603_7f63d6e2ce0a

#include "translator/mathOperators/AdditionOperator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The AdditionOperatorCreator class
 */
class AdditionOperatorCreator : public TranslationCreatorBase
{
public:
    typedef AdditionOperatorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of AdditionOperatorCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of AdditionOperatorCreator
    virtual ~AdditionOperatorCreator();

    /**
     * @brief Create Pointer to class AdditionOperator
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new AdditionOperator
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return AdditionOperator
     */
    static std::string get_class_name() { return "AdditionOperator"; }
    
protected:
    /// Create an instance of AdditionOperatorCreator
    AdditionOperatorCreator();

private:
    AdditionOperatorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorAdditionOperatorCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer additionoperator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _34072676_d7ea_4e61_8603_7f63d6e2ce0a
