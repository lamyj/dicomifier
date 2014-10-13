/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e7244a16_a29c_4f85_ac52_002af1ed5e31
#define _e7244a16_a29c_4f85_ac52_002af1ed5e31

#include "translator/generator/UIDGenerator.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class UIDGeneratorCreator : public TranslationCreatorBase
{
public:
    typedef UIDGeneratorCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~UIDGeneratorCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "UIDGenerator"; }
    
protected:
    UIDGeneratorCreator();

private:
    UIDGeneratorCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorUIDGeneratorCreator
    {
        std::string uidtype;
        mutable dicomifier::translator::Tag::Pointer uidgenerator;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
#endif // _e7244a16_a29c_4f85_ac52_002af1ed5e31
