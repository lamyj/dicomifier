/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "AcquisitionMatrixDcmField.h"
#include "core/Logger.h"

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
AcquisitionMatrixDcmField<VR>
::AcquisitionMatrixDcmField()
    :SubTag<VR>()
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
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    // Clean residual values
    this->_array.clear();

    if (!brukerdataset->has_field("VisuAcqImagePhaseEncDir"))
    {
        this->_array.push_back(0);
        this->_array.push_back(0);
        this->_array.push_back(0);
        this->_array.push_back(0);
        return;
    }
    
    std::string const brukerfield = 
        brukerdataset->get_field("VisuAcqImagePhaseEncDir").
            get_string(generator.get_step());

    Uint16 value1 = brukerdataset->get_field("VisuAcqSize").get_int(0);
    Uint16 value2 = brukerdataset->get_field("VisuAcqSize").get_int(1);
    
    if (brukerfield.find("col") != std::string::npos ||
        brukerfield.find("COL") != std::string::npos)
    {
        this->_array.push_back(value1);
        this->_array.push_back(0);
        this->_array.push_back(0);
        this->_array.push_back(value2);
    }
    else if (brukerfield.find("row") != std::string::npos ||
             brukerfield.find("ROW") != std::string::npos)
    {
        this->_array.push_back(0);
        this->_array.push_back(value1);
        this->_array.push_back(value2);
        this->_array.push_back(0);
    }
    else
    {
        std::stringstream stream;
        stream << "Bad value for VisuAcqImagePhaseEncDir: " << brukerfield;
        throw DicomifierException(stream.str());
    }
}

template<DcmEVR VR>
void
AcquisitionMatrixDcmField<VR>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be US for Tag 0018,1310.");
}
   
} // namespace translator

} // namespace dicomifier
