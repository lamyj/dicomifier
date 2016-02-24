/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a08c5c74_8a9e_44bd_aa37_34073df96613
#define _a08c5c74_8a9e_44bd_aa37_34073df96613

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/**
 * @brief read_bruker_directory
 * @param args[0]: bruker directory path
 * @param args[1]: Series Number
 * @return Bruker Dataset as JSON representation
 */
v8::Handle<v8::Value> read_bruker_directory(v8::Arguments const & args);

/**
 * @brief Convert pixel data to DICOM
 * @param args[0]: Bruker data set
 * @param args[1]: frames count, to split frame data (optional)
 */
v8::Handle<v8::Value>
convertPixelDataToDicom(v8::Arguments const & args);

}

}

#endif // _a08c5c74_8a9e_44bd_aa37_34073df96613

