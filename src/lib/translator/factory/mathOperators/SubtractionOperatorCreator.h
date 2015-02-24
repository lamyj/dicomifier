/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0012a674_5c23_40e0_bda3_5cd7d1bb9790
#define _0012a674_5c23_40e0_bda3_5cd7d1bb9790

#include "translator/mathOperators/SubtractionOperator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The SubtractionOperatorCreator class
 */
class SubtractionOperatorCreator : public TranslationCreatorBase
{
public:
    typedef SubtractionOperatorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SubtractionOperatorCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of SubtractionOperatorCreator
    virtual ~SubtractionOperatorCreator();

    /**
     * @brief Create Pointer to class SubtractionOperator
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new SubtractionOperator
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return SubtractionOperator
     */
    static std::string get_class_name() { return "SubtractionOperator"; }

protected:
    /// Create an instance of SubtractionOperatorCreator
    SubtractionOperatorCreator();

private:
    SubtractionOperatorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorSubtractionOperatorCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer subtractionoperator;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _0012a674_5c23_40e0_bda3_5cd7d1bb9790
