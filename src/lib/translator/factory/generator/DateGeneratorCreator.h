/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e89d5507_5799_44c7_a2a4_da4fc1ab2443
#define _e89d5507_5799_44c7_a2a4_da4fc1ab2443

#include "translator/generator/DateGenerator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class DateGeneratorCreator : public TranslationCreatorBase
{
public:
    typedef DateGeneratorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~DateGeneratorCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "DateGenerator"; }
    
protected:
    DateGeneratorCreator();

private:
    DateGeneratorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDateGeneratorCreator
    {
        std::string inputformat;
        std::string outputformat;
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer dategenerator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _e89d5507_5799_44c7_a2a4_da4fc1ab2443

