/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fc667598_ca87_4de0_a991_3873136cf82c
#define _fc667598_ca87_4de0_a991_3873136cf82c

#include "translator/conditions/BrukerFieldExist.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{

namespace translator
{
    
namespace factory
{
    
class BrukerFieldExistCreator : public TranslationCreatorBase
{
public:
    typedef BrukerFieldExistCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~BrukerFieldExistCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "BrukerFieldExist"; }
    
protected:
    BrukerFieldExistCreator();
    
private:
    BrukerFieldExistCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};

}
    
}

}

#endif // _fc667598_ca87_4de0_a991_3873136cf82c
