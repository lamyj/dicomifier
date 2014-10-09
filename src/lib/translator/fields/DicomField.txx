/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "DicomField.h"
#include "translator/SubTag.h"
#include "translator/fields/BrukerField.h"
#include "translator/fields/ConstantField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DicomField<VR>::Pointer
DicomField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename DicomField<VR>::Pointer
DicomField<VR>
::New(dicomifier::TagAndRange const & tagrange, Tag::Pointer tag)
{
    return Pointer(new Self(tagrange, tag));
}
    
template<DcmEVR VR>
DicomField<VR>
::DicomField()
    :Tag(), _tag(NULL)
{
    // Nothing to do
}
 
template<DcmEVR VR>
DicomField<VR>
::DicomField(dicomifier::TagAndRange const & tagrange, Tag::Pointer tag)
    :Tag(), _dicomtags(tagrange), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
DicomField<VR>
::~DicomField()
{
    // Nothing to do
}

template<DcmEVR VR>
void
DicomField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      std::vector<int> const & indexes,
      DcmDataset* dataset)
{    
    if (this->_tag == NULL)
    {
        throw DicomifierException("Cannot run DicomField.");
    }
    
    if (dataset == NULL)
    {
        throw DicomifierException("Empty dataset.");
    }
    
    if(!dataset->tagExists(this->_dicomtags._tag))
    {
        dataset->insertEmptyElement(this->_dicomtags._tag);
    }
    
    DcmElement * element = NULL;
    OFCondition const element_ok =
        dataset->findAndGetElement(this->_dicomtags._tag, element);
        
    this->_tag->run(brukerdataset, indexes, dataset);
        
    std::vector<ValueType> values;
    
    if (this->_tag->get_class_type() != ECT_TestField)
    {
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);
        values = subtag->get_array();
    }
        
    OFCondition const set_ok = ElementTraits<VR>::array_setter(element, 
                                                               &values[0], 
                                                               values.size());
    if(set_ok.bad())
    {
        throw DicomifierException("DicomField::run(): Could not set array");
    }
}
    
} // namespace translator
    
} // namespace dicomifier
