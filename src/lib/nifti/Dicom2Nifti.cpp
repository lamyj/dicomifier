/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <dcmtkpp/conversion.h>
#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/json_converter.h>
#include <dcmtkpp/Reader.h>
#include <dcmtkpp/registry.h>

#include "core/DicomifierException.h"
#include "core/Logger.h"
#include "Dicom2Nifti.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace nifti
{

Dicom2Nifti::Pointer
Dicom2Nifti
::New()
{
    return Pointer(new Self());
}

Dicom2Nifti::Pointer
Dicom2Nifti
::New(std::string const & dicomDir, std::string const & outputDir,
      int outputDimension)
{
    return Pointer(new Self(dicomDir, outputDir, outputDimension));
}

Dicom2Nifti
::Dicom2Nifti():
    _dicomDir(""), _outputDir(""),
    _outputDimension(4)
{
    // Nothing to do
}

Dicom2Nifti
::Dicom2Nifti(std::string const & dicomDir, std::string const & outputDir,
              int outputDimension):
    _dicomDir(dicomDir), _outputDir(outputDir),
    _outputDimension(outputDimension)
{
    // Nothing to do
}

Dicom2Nifti
::~Dicom2Nifti()
{
    // Nothing to do
}

std::string const &
Dicom2Nifti
::get_dicomDir() const
{
    return this->_dicomDir;
}

void
Dicom2Nifti
::set_dicomDir(std::string const & dicomDir)
{
    this->_dicomDir = dicomDir;
}

std::string const &
Dicom2Nifti
::get_outputDir() const
{
    return this->_outputDir;
}

void
Dicom2Nifti
::set_outputDir(std::string const & outputDir)
{
    this->_outputDir = outputDir;
}

int
Dicom2Nifti
::get_outputDimension() const
{
    return this->_outputDimension;
}

void
Dicom2Nifti
::set_outputDimension(int outputDimension)
{
    this->_outputDimension = outputDimension;
}

void
Dicom2Nifti
::run() const
{
    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(this->_dicomDir) )
    {
        throw DicomifierException("Input not a Directory: " + this->_dicomDir);
    }

    javascript::JavascriptVM jsvm;

    typedef boost::filesystem::directory_iterator Iterator;

    std::vector<std::string> list_dataset;

    for(Iterator it(boost::filesystem::path(this->_dicomDir));
        it != Iterator(); ++it)
    {
        if(boost::filesystem::is_regular_file(*it))
        {
            list_dataset.push_back(boost::filesystem::path(*it).c_str());
        }
    }

    std::sort(list_dataset.begin(), list_dataset.end());
    loggerDebug() << "Processing " << list_dataset.size() << " files...";

    std::stringstream streamstr;
    streamstr << "require('dicom2nifti/converter.js');\n";
    for (unsigned int i = 0; i < list_dataset.size(); ++i)
    {
        streamstr << "dicomifier.inputs[" << i << "] = \""
                  << list_dataset[i] << "\";\n";
    }

    if(this->_outputDimension != 3 && this->_outputDimension != 4)
    {
        throw DicomifierException("Unknown dimension");
    }

    streamstr << "dicomifier.dicom2nifti.convert(dicomifier.inputs, "
              << this->_outputDimension << ", '" << this->_outputDir << "');";
    jsvm.run(streamstr.str(), jsvm.get_context());

    loggerDebug() << "Done.";
}

nifti_image *
Dicom2Nifti
::extract_information_from_dataset(Json::Value const & dataset,
                                   std::string const & filename,
                                   int dimension)
{
    // fill out the image header.
    nifti_image * nim = nifti_simple_init_nim();

    char * tempbasename = nifti_makebasename(filename.c_str());
    std::string const BaseName(tempbasename);
    free(tempbasename);

    nim->nifti_type = NIFTI_FTYPE_NIFTI1_1;

    nim->fname = nifti_makehdrname(BaseName.c_str(),
                                   nim->nifti_type, false, false);
    nim->iname = nifti_makeimgname(BaseName.c_str(),
                                   nim->nifti_type, false, false);

    // Initialize fields
    nim->nvox = 1;

    nim->xyz_units= static_cast< int >( NIFTI_UNITS_MM | NIFTI_UNITS_UNKNOWN );
    nim->dim[7] = nim->nw=1;
    nim->dim[6] = nim->nv=1;
    nim->dim[5] = nim->nu=1;
    nim->dim[4] = nim->nt=1;
    nim->dim[3] = nim->nz=1;
    nim->dim[2] = nim->ny=1;
    nim->dim[1] = nim->nx=1;

    Dicom2Nifti::extract_stack_number(dataset, dimension, nim);

    nim->pixdim[3] = nim->dz =
            static_cast<float>(Dicom2Nifti::get_distance_between_slice(dataset));
    nim->nvox *= nim->dim[3];

    nim->dim[2] = nim->ny = dataset.get("Columns", Json::Value())[0].asInt();
    nim->pixdim[2] = nim->dy =
            static_cast<float>( dataset.get("PixelSpacing",
                                            Json::Value())[1].asDouble() );
    nim->nvox *= nim->dim[2];

    nim->dim[1] = nim->nx = dataset.get("Rows", Json::Value())[0].asInt();
    nim->pixdim[1] = nim->dx =
            static_cast<float>( dataset.get("PixelSpacing",
                                            Json::Value())[0].asDouble() );
    nim->nvox *= nim->dim[1];

    // Datatype
    nim->datatype = DT_INT16;
    nim->nbyper = 2;

    nim->scl_slope = 1.0f;
    nim->scl_inter = 0.0f;

    // SetNIfTIOrientationFromImageIO
    // use NIFTI method 2
    nim->sform_code = NIFTI_XFORM_SCANNER_ANAT;
    nim->qform_code = NIFTI_XFORM_ALIGNED_ANAT;

    // Get 3 vectors for directions
    Json::Value const image_orientation_patient =
            Dicom2Nifti::extract_orientation(dataset);

    std::vector<double> directions;
    // Get dir x and y
    for (unsigned int i = 0; i < image_orientation_patient.size(); ++i)
    {
        directions.push_back(image_orientation_patient[i].asDouble());
    }
    // Compute dir z
    directions.push_back(directions[1] * directions[5] -
                         directions[2] * directions[4]);
    directions.push_back(directions[2] * directions[3] -
                         directions[0] * directions[5]);
    directions.push_back(directions[0] * directions[4] -
                         directions[1] * directions[3]);

    mat44 matrix2 =
        nifti_make_orthog_mat44(-directions[0],-directions[1],directions[2],
                                -directions[3],-directions[4],directions[5],
                                -directions[6],-directions[7],directions[8]);

    // transpose
    mat44 matrix;
    for ( unsigned int i = 0; i < 4; i++ )
    {
        for ( unsigned int j = 0; j < 4; j++ )
        {
            matrix.m[i][j] = matrix2.m[j][i];
        }
    }

    // Fill in origin.
    Json::Value const image_position_patient =
            Dicom2Nifti::extract_position(dataset);

    matrix.m[0][3] =
            static_cast<float>(-image_position_patient[0][0].asDouble());
    matrix.m[1][3] =
            static_cast<float>(-image_position_patient[0][1].asDouble());
    //NOTE:  The final dimension is not negated!
    matrix.m[2][3] =
            static_cast<float>( image_position_patient[0][2].asDouble());

    nifti_mat44_to_quatern(matrix,
                           &(nim->quatern_b),
                           &(nim->quatern_c),
                           &(nim->quatern_d),
                           &(nim->qoffset_x),
                           &(nim->qoffset_y),
                           &(nim->qoffset_z),
                           NULL,
                           NULL,
                           NULL,
                           &(nim->qfac));
    // copy q matrix to s matrix
    nim->qto_xyz =  matrix;
    nim->sto_xyz =  matrix;

    for(unsigned int i = 0; i < 3; ++i)
    {
        for(unsigned int j = 0; j < 3; ++j)
        {
            nim->sto_xyz.m[i][j] = nim->pixdim[j+1] * nim->sto_xyz.m[i][j];
        }
    }
    nim->sto_ijk = nifti_mat44_inverse(nim->sto_xyz);
    nim->qto_ijk = nifti_mat44_inverse(nim->qto_xyz);

    nim->pixdim[0] = nim->qfac;

    // Create buffer image:
    std::vector<uint8_t> buffer;

    Json::Value const pixeldata = dataset.get("PixelData", Json::Value());
    for (unsigned int i = 0; i < pixeldata.size(); ++i)
    {
        auto const & encoded = pixeldata[i].asString();
        OFString const encoded_dcmtk(encoded.c_str());
        unsigned char * decoded;
        size_t const decoded_size =
            OFStandard::decodeBase64(encoded_dcmtk, decoded);

        buffer.resize(buffer.size() + decoded_size);
        std::copy(decoded, decoded + decoded_size, buffer.end() - decoded_size);

        delete[] decoded;
    }

    uint8_t * data = new uint8_t[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), data);

    nim->data = reinterpret_cast<void*>(data);

    return nim;
}

void
Dicom2Nifti
::extract_stack_number(Json::Value const & dataset,
                       int dimension, nifti_image *nim)
{
    std::string const sopclassuid = dataset.get("SOPClassUID",
                                                Json::Value())[0].asString();

    if (sopclassuid == UID_MRImageStorage)
    {
        // One stack = 3 dimensions
        // Multi stack = 4 dimensions
        nim->ndim = (int)dimension;
        nim->dim[0] = (int)dimension;

        if (dimension == 4)
        {
            nim->dim[4] = nim->nt = dataset.get("DICOMIFIER_STACKS_NUMBER",
                                                Json::Value()).asInt();
            nim->pixdim[4] = nim->dt = 1;
            nim->nvox *= nim->dim[4];

            // Get number of dataset in the stack
            // we suppose each stack contains the same number of datasets
            Json::Value dsnumber_json =
                    dataset.get("DICOMIFIER_DATASET_PERSTACK_NUMBER",
                                Json::Value());
            if (dsnumber_json.empty())
            {
                nim->dim[3] = nim->nz = 1;
            }
            else
            {
                unsigned int dsnumber = dsnumber_json[0].asInt();

                nim->dim[3] = nim->nz = dsnumber;
            }
        }
        else
        {
            // Get number of dataset in the stack
            unsigned int dsnumber =
                    dataset.get("PixelData", Json::Value()).size();
            nim->dim[3] = nim->nz = dsnumber;
        }
    }
    else if (sopclassuid == UID_EnhancedMRImageStorage)
    {
        if (dimension == 3)
        {
            loggerWarning() << "force NIfTI 4 dimension.";
        }

        int stack_number = 0;
        int ds_perstack_number = 0;
        // Get number of Stack:
        for (auto value : dataset.get("PerFrameFunctionalGroupsSequence",
                                      Json::Value()))
        {
            auto const strstackid =
                    value.get("FrameContentSequence", Json::Value())[0].
                          get("StackID", Json::Value())[0].asString();
            int const instackpos =
                    value.get("FrameContentSequence", Json::Value())[0].
                          get("InStackPositionNumber", Json::Value())[0].asInt();

            if (instackpos > ds_perstack_number)
            {
                ds_perstack_number = instackpos;
            }

            int stackid = boost::lexical_cast<int>(strstackid);
            if (stackid > stack_number)
            {
                stack_number = stackid;
            }
        }

        nim->dim[4] = nim->nt = stack_number;
        nim->pixdim[4] = nim->dt = 1;
        nim->nvox *= nim->dim[4];

        // we suppose each stack contains the same number of datasets
        nim->dim[3] = nim->nz = ds_perstack_number;
    }
}

Json::Value
Dicom2Nifti
::extract_orientation(Json::Value const & dataset)
{
    std::string const sopclassuid = dataset.get("SOPClassUID",
                                                Json::Value())[0].asString();

    Json::Value image_orientation_patient;

    if (sopclassuid == UID_MRImageStorage)
    {
        // Get 3 vectors for directions
        image_orientation_patient =
                dataset.get("ImageOrientationPatient", Json::Value());
    }
    else if (sopclassuid == UID_EnhancedMRImageStorage)
    {
        // Get ImageOrientationPatient for the first frame
        image_orientation_patient =
                dataset.get("PerFrameFunctionalGroupsSequence",
                            Json::Value())[0].
                        get("PlaneOrientationSequence", Json::Value())[0].
                        get("ImageOrientationPatient", Json::Value());
    }

    if (image_orientation_patient.isNull())
    {
        throw new DicomifierException("Missing ImageOrientationPatient");
    }

    return image_orientation_patient;
}

Json::Value
Dicom2Nifti
::extract_position(Json::Value const & dataset)
{
    std::string const sopclassuid = dataset.get("SOPClassUID",
                                                Json::Value())[0].asString();

    Json::Value image_position_patient;

    if (sopclassuid == UID_MRImageStorage)
    {
        // Get 3 vectors for directions
        image_position_patient =
                dataset.get("ImagePositionPatient", Json::Value());
    }
    else if (sopclassuid == UID_EnhancedMRImageStorage)
    {
        // Get ImageOrientationPatient for the first frame
        Json::Value array(Json::ValueType::arrayValue);
        array.append(
                dataset.get("PerFrameFunctionalGroupsSequence",
                            Json::Value())[0].
                        get("PlanePositionSequence", Json::Value())[0].
                        get("ImagePositionPatient", Json::Value()));

        image_position_patient = array;
    }

    if (image_position_patient.isNull())
    {
        throw new DicomifierException("Missing ImagePositionPatient");
    }

    return image_position_patient;
}

double
Dicom2Nifti
::get_distance_between_slice(Json::Value const & dataset)
{
    Json::Value const image_position_patient =
            dataset.get("ImagePositionPatient", Json::Value());
    if (image_position_patient.size() < 2)
    {
        return 1; // default
    }

    std::vector<double> diff;

    for (unsigned int i = 0; i < image_position_patient[0].size(); ++i)
    {
        double value1 = image_position_patient[0][i].asDouble();
        double value2 = image_position_patient[1][i].asDouble();
        diff.push_back(value2 - value1);
    }

    double distance = 0;
    for (double value : diff)
    {
        distance += (value * value);
    }

    return sqrt(distance);
}

} // namespace nifti

} // namespace dicomifier
