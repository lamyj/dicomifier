/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

%module dicomifier
%{
#include "core/DicomifierException.h"
#include "wrapper.h"
%}

%include std_except.i
%include std_string.i

%include core/DicomifierException.h   
%include wrapper.h

%pythoncode
%{
def DicomifierException__str__(self):
    return self.what()
DicomifierException.__str__ = DicomifierException__str__
%}
