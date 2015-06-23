/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _35468c0a_e808_4335_ac3a_e1b435f4560b
#define _35468c0a_e808_4335_ac3a_e1b435f4560b

#include "bruker/converters/equipment.h"
#include "bruker/converters/frame_of_reference.h"
#include "bruker/converters/image.h"
#include "bruker/converters/mr_image.h"
#include "bruker/converters/patient.h"
#include "bruker/converters/series.h"
#include "bruker/converters/study.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::vector<std::map<dcmtkpp::Tag, converter_base::pointer>> const mr_image_storage = {
    patient,
    general_study, patient_study,
    general_series,
    frame_of_reference,
    general_equipment,
    general_image, image_plane, image_pixel, mr_image,
    sop_common,
};


}

}

}

#endif // _35468c0a_e808_4335_ac3a_e1b435f4560b
