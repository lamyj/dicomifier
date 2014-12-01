/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1fc05880_7487_48d3_b15f_8609973a7de1
#define _1fc05880_7487_48d3_b15f_8609973a7de1

#include "translator/fields/DicomField.h"
#include "translator/fields/DicomSequenceField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
class DicomFieldCreator : public TranslationCreatorBase
{
public:
    typedef DicomFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~DicomFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    static std::string get_class_name() { return "DicomField"; }

protected:
    DicomFieldCreator();

private:
    DicomFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDicomFieldCreator
    {
        dicomifier::TagAndRange tagrange;
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        bool perframe;
        mutable dicomifier::translator::Tag::Pointer dicomfield;
        template<DcmEVR VR> void run() const;
    };
    
};
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _1fc05880_7487_48d3_b15f_8609973a7de1
