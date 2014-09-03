/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fa5422c1_776b_4c6d_8141_773123559763
#define _fa5422c1_776b_4c6d_8141_773123559763

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class BrukerFieldCreator : public TranslationCreatorBase
{
public:
    typedef BrukerFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~BrukerFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "BrukerField"; }

protected:
    BrukerFieldCreator();

private:
    BrukerFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorBrukerFieldCreator
    {
        std::string brukerfieldname;
        mutable dicomifier::translator::Tag::Pointer brukerField;
        template<DcmEVR VR> void run() const;
    };
    
};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _fa5422c1_776b_4c6d_8141_773123559763
