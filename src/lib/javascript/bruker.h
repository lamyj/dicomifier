/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a08c5c74_8a9e_44bd_aa37_34073df96613
#define _a08c5c74_8a9e_44bd_aa37_34073df96613

#include <string>

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

void get_pixeldata_information(v8::Local<v8::Object> const & data_set,
                               std::string & pixel_data,
                               std::string & word_type,
                               std::string & byte_order,
                               int & frame_size);

/**
 * @brief Get pixel data as base64 String
 * @param args: 3 arguments:
 *              - BrukerDataset (JSON bruker dataset,
 *              - Number of Frame (int),
 *              - All_data (bool)
 * @return array of base64 String
 */
v8::Handle<v8::Value> load_pixel_data(v8::Arguments const & args);

v8::Handle<v8::Value> sort_pixel_data(v8::Arguments const & args);

/**
 * @brief read_bruker_directory
 * @param args[0]: bruker directory path
 * @param args[1]: Series Number
 * @return Bruker Dataset as JSON representation
 */
v8::Handle<v8::Value> read_bruker_directory(v8::Arguments const & args);

}

}

#endif // _a08c5c74_8a9e_44bd_aa37_34073df96613

