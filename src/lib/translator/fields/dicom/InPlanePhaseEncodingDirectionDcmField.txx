/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InPlanePhaseEncodingDirectionDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename InPlanePhaseEncodingDirectionDcmField<VR>::Pointer
InPlanePhaseEncodingDirectionDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
InPlanePhaseEncodingDirectionDcmField<VR>
::InPlanePhaseEncodingDirectionDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
InPlanePhaseEncodingDirectionDcmField<VR>
::~InPlanePhaseEncodingDirectionDcmField()
{
    // Nothing to do
}

template<>
void
InPlanePhaseEncodingDirectionDcmField<EVR_CS>
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

    std::string const brukerfield =
        brukerdataset->GetFieldData("VisuAcqImagePhaseEncDir")->
            get_string(generator.get_step());
    
    if (brukerfield == "col_dir")
    {
        this->_array.push_back("COL");
    }
    else if (brukerfield == "row_dir")
    {
        this->_array.push_back("ROW");
    }
    else
    {
        std::stringstream stream;
        stream << "Bad value for VisuAcqImagePhaseEncDir field: " << brukerfield;
        throw DicomifierException(stream.str());
    }
}

template<DcmEVR VR>
void
InPlanePhaseEncodingDirectionDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be CS for Tag 0018,1312.");
}
    
} // namespace dicomifier

} // namespace translator
