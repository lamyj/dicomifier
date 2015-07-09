/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "DicomField.h"
#include "TestField.h"
#include "translator/SubTag.h"

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
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
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
    OFCondition condition =
        dataset->findAndGetElement(this->_dicomtags._tag, element);
    if (condition.bad())
    {
        throw DicomifierException(condition.text());
    }
        
    this->_tag->run(brukerdataset, generator, dataset);
        
    if (VR != EVR_AT)
    {
        if (element != NULL)
        {
            std::vector<ValueType> values;

            typename TestField::Pointer tagtest =
                std::dynamic_pointer_cast<TestField>(this->_tag);
            if (tagtest == NULL)
            {
                typename SubTag<VR>::Pointer subtag =
                    std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);
                values = subtag->get_array();
            }

            condition = ElementTraits<VR>::array_setter(element, &values[0],
                                                        values.size());
        }

        if(condition.bad() || element == NULL)
        {
            throw DicomifierException("DicomField::run(): Could not set array");
        }
    }
    else // VR == AT
    {
        if (element != NULL)
        {
            std::vector<Uint16> values;

            typename SubTag<EVR_AT>::Pointer subtag =
                std::dynamic_pointer_cast<SubTag<EVR_AT>>(this->_tag);

            if (subtag != NULL)
            {
                values = subtag->get_array();
            }

            condition = element->putUint16Array(&values[0], values.size()/2);
        }
        
        if(condition.bad() || element == NULL)
        {
            throw DicomifierException("DicomField::run(): Could not set array");
        }
    }
}
    
} // namespace translator
    
} // namespace dicomifier
