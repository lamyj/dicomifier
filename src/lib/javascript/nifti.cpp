/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "javascript/nifti.h"

#include <clocale>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>
#include <nifti1_io.h>
#include <v8.h>

#include "javascript/common.h"
#include "nifti/Dicom2Nifti.h"

namespace dicomifier
{

namespace javascript
{

v8::Handle<v8::Value> write_nifti(v8::Arguments const & args)
{
    if(args.Length() < 4)
    {
        return v8::ThrowException(
                v8::String::New("Missing Arguments for writeNIfTI"));
    }

    try
    {
        // Get the JSON representation of the V8 data set.
        std::string json = *v8::String::Utf8Value(args[0]);

        // Parse it into a data set.
        Json::Value jsondataset;
        {
            Json::Reader reader;
            std::string old_locale = std::setlocale(LC_ALL, "C");
            reader.parse(json, jsondataset);
            std::setlocale(LC_ALL, old_locale.c_str());
        }

        int const dimension = as_scalar<double>(args[1]);

        // Write Nifti image file
        auto const path_nii = as_scalar<std::string>(args[2]);

        boost::filesystem::path const destination(path_nii);
        boost::filesystem::create_directories(destination.parent_path());

        nifti_image * nim =
            nifti::Dicom2Nifti::extract_information_from_dataset(
                jsondataset, path_nii, dimension);
        nifti_image_write(nim);
        delete[] reinterpret_cast<uint8_t*>(nim->data);
        nim->data = 0; // if left pointing to data buffer
        // nifti_image_free will try and free this memory
        nifti_image_free(nim);

        // Write Metadata file
        auto const path_json = as_scalar<std::string>(args[3]);

        boost::filesystem::path const destinationjson(path_json);
        boost::filesystem::create_directories(destinationjson.parent_path());

        jsondataset.removeMember("PixelData");
        jsondataset.removeMember("DICOMIFIER_STACKS_NUMBER");
        jsondataset.removeMember("DICOMIFIER_DATASET_PERSTACK_NUMBER");
        std::ofstream myfile(path_json);
        myfile << jsondataset.toStyledString();
    }
    catch (std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

}

}
