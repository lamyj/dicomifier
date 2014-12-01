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
    
class SubtractionOperatorCreator : public TranslationCreatorBase
{
public:
    typedef SubtractionOperatorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~SubtractionOperatorCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "SubtractionOperator"; }

protected:
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
