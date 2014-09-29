/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _28a8d2a5_1e09_40b5_a218_a5f001c649c5
#define _28a8d2a5_1e09_40b5_a218_a5f001c649c5

#include "translator/generator/UpperCaseGenerator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class UpperCaseGeneratorCreator : public TranslationCreatorBase
{
public:
    typedef UpperCaseGeneratorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~UpperCaseGeneratorCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "UpperCaseGenerator"; }
    
protected:
    UpperCaseGeneratorCreator();

private:
    UpperCaseGeneratorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorUpperCaseGeneratorCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer uppercasegenerator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _28a8d2a5_1e09_40b5_a218_a5f001c649c5


