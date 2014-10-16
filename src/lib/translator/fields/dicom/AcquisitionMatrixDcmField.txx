/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "AcquisitionMatrixDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename AcquisitionMatrixDcmField<VR>::Pointer
AcquisitionMatrixDcmField<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename AcquisitionMatrixDcmField<VR>::Pointer
AcquisitionMatrixDcmField<VR>
::New(Tag::Pointer tag)
{
    return Pointer(new Self(tag));
}

template<DcmEVR VR>
AcquisitionMatrixDcmField<VR>
::AcquisitionMatrixDcmField()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
AcquisitionMatrixDcmField<VR>
::AcquisitionMatrixDcmField(Tag::Pointer tag)
    :SubTag<VR>(), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
AcquisitionMatrixDcmField<VR>
::~AcquisitionMatrixDcmField()
{
    // Nothing to do
}

template<>
void
AcquisitionMatrixDcmField<EVR_US>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    if (this->_tag == NULL)
    {
        throw DicomifierException("Missing node");
    }
    
    std::string const brukerfield = 
        brukerdataset->GetFieldData("VisuAcqImagePhaseEncDir")->
            get_string(generator.get_step());
    
    typename SubTag<EVR_US>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<EVR_US>>(this->_tag);

    subtag->run(brukerdataset, generator, dataset);
    
    auto array = subtag->get_array();
    
    if (brukerfield == "col_dir")
    {
        this->_array.push_back(array[0]);
        this->_array.push_back(0);
        this->_array.push_back(0);
        this->_array.push_back(array[1]);
    }
    else //if (brukerfield == "row_dir")
    {
        this->_array.push_back(0);
        this->_array.push_back(array[0]);
        this->_array.push_back(array[1]);
        this->_array.push_back(0);
    }
}

template<DcmEVR VR>
void
AcquisitionMatrixDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be US for Tag 0018,1310.");
}
   
} // namespace translator

} // namespace dicomifier
