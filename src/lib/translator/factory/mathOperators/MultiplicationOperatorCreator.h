/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9b082916_d82a_484b_979f_92378e0b4a0a
#define _9b082916_d82a_484b_979f_92378e0b4a0a

#include "translator/mathOperators/MultiplicationOperator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The MultiplicationOperatorCreator class
 */
class MultiplicationOperatorCreator : public TranslationCreatorBase
{
public:
    typedef MultiplicationOperatorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of MultiplicationOperatorCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of MultiplicationOperatorCreator
    virtual ~MultiplicationOperatorCreator();

    /**
     * @brief Create Pointer to class MultiplicationOperator
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new MultiplicationOperator
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return MultiplicationOperator
     */
    static std::string get_class_name() { return "MultiplicationOperator"; }

protected:
    /// Create an instance of MultiplicationOperatorCreator
    MultiplicationOperatorCreator();

private:
    MultiplicationOperatorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorMultiplicationOperatorCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer multiplicationoperator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _9b082916_d82a_484b_979f_92378e0b4a0a

