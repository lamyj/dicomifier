/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <memory>

#include "dicom/Dictionaries.h"
#include "wrapper.h"

void execute(std::string xmlfile, std::string privatedictionary) throw (dicomifier::DicomifierException)
{
    if (privatedictionary != "")
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary(privatedictionary);
    }

    // TODO
}
