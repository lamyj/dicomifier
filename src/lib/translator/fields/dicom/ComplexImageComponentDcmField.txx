/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ComplexImageComponentDcmField.h"

namespace dicomifier
{

namespace translator
{

template<DcmEVR VR>
typename ComplexImageComponentDcmField<VR>::Pointer
ComplexImageComponentDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
ComplexImageComponentDcmField<VR>
::ComplexImageComponentDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
ComplexImageComponentDcmField<VR>
::~ComplexImageComponentDcmField()
{
    // Nothing to do
}

template<>
void
ComplexImageComponentDcmField<EVR_CS>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    // Clean residual values
    this->_array.clear();

    std::string brukerfield = brukerdataset->GetFieldData("VisuCoreFrameType")->get_string(0);

    if (brukerfield == "MAGNITUDE_IMAGE")
    {
        this->_array.push_back("MAGNITUDE");
    }
    else if (brukerfield == "PHASE_IMAGE")
    {
        this->_array.push_back("PHASE");
    }
    else if (brukerfield == "REAL_IMAGE")
    {
        this->_array.push_back("REAL");
    }
    else if (brukerfield == "IMAGINARY_IMAGE")
    {
        this->_array.push_back("IMAGINARY");
    }
    else if (brukerfield == "MIXED_IMAGE")
    {
        this->_array.push_back("MIXED");
    }
    else
    {
        throw DicomifierException("Unknown value " + brukerfield + " for VisuCoreFrameType field.");
    }
}

template<DcmEVR VR>
void
ComplexImageComponentDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be CS for Tag 0008,9208.");
}

} // namespace translator

} // namespace dicomifier
