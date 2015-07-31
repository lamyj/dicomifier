/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <string>

#include "core/DicomifierException.h"

void execute(std::string const & bruker_directory,
             std::string const & dicom_directory,
             std::string const & study_number,
             std::string const & series_number,
             std::string privatedictionary = "") throw (dicomifier::DicomifierException);
