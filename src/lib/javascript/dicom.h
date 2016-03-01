/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _be72f1ef_933a_48ef_b202_867bfbfbbb5c
#define _be72f1ef_933a_48ef_b202_867bfbfbbb5c

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/**
 * @brief read_dicom
 * @param args[0]: DICOM file path
 * @return DICOM dataset as JSON representation
 */
v8::Handle<v8::Value> read_dicom(v8::Arguments const & args);

/**
 * @brief write_dicom
 * @param args[0]: DICOM dataset as JSON representation
 * @param args[1]: DICOM file path
 * @param args[2]: Transfer Syntax
 * @return NULL if no error occured
 */
v8::Handle<v8::Value> write_dicom(v8::Arguments const & args);

/**
 * @brief generate_dicom_filename
 * @param args
 * @return
 */
v8::Handle<v8::Value> generate_dicom_filename(v8::Arguments const & args);

v8::Handle<v8::Value> generate_uid(v8::Arguments const &);

}

}

#endif // _be72f1ef_933a_48ef_b202_867bfbfbbb5c

