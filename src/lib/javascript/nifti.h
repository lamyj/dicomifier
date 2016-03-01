/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a878a1f7_e935_4120_aed6_a44b44c262d8
#define _a878a1f7_e935_4120_aed6_a44b44c262d8

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/**
 * @brief write_nifti
 * @param args[0]: DICOM dataset as JSON representation
 * @param args[1]: dimension of output NIfTI (3D or 4D)
 * @param args[2]: NIfTI file name (image)
 * @param args[3]: JSON file name (metadata)
 * @return NULL if no error occured
 */
v8::Handle<v8::Value> write_nifti(v8::Arguments const & args);

}

}

#endif // _a878a1f7_e935_4120_aed6_a44b44c262d8

