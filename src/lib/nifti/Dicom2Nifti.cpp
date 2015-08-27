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

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>     /* Covers most common dcmdata classes */
#include <dcmtk/ofstd/ofstd.h>

#include <dcmtkpp/conversion.h>
#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/json_converter.h>
//#include <dcmtkpp/Reader.h>
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
::New(const std::string &dicomDir, const std::string &outputDir)
{
    return Pointer(new Self(dicomDir, outputDir));
}

Dicom2Nifti
::Dicom2Nifti():
    _dicomDir(""), _outputDir("")
{
    // Nothing to do
}

Dicom2Nifti
::Dicom2Nifti(std::string const & dicomDir, std::string const & outputDir):
    _dicomDir(dicomDir), _outputDir(outputDir)
{

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

    unsigned int count = 0;
    for(Iterator it(boost::filesystem::path(this->_dicomDir));
        it != Iterator(); ++it)
    {
        if(boost::filesystem::is_regular_file(*it))
        {
            // Next version of dcmtkpp
            //std::ifstream stream(boost::filesystem::path(*it).c_str(),
            //                     std::ios::in | std::ios::binary);
            //
            //std::pair<dcmtkpp::DataSet, dcmtkpp::DataSet> file;
            dcmtkpp::DataSet dataset;
            try
            {
                // Next version of dcmtkpp
                //file = dcmtkpp::Reader::read_file(stream);

                DcmFileFormat file;
                OFCondition const condition = file.loadFile(boost::filesystem::path(*it).c_str());

                if(condition.bad())
                {
                    std::stringstream streamerror;
                    streamerror << "Cannot read dataset: " << condition.text();
                    throw DicomifierException(streamerror.str());
                }

                dataset = dcmtkpp::convert(file.getAndRemoveDataset());
            }
            catch(std::exception const & e)
            {
                std::cout << "Could not read " << *it << ": "
                          << e.what() << "\n";
            }

            if (!dataset.has(dcmtkpp::registry::PixelData))
            {
                // ignore file
                continue;
            }

            auto const json_dicom_dataset = dcmtkpp::as_json(dataset);

            std::stringstream streamstr;
            streamstr << "dicomifier.inputs[" << count << "] = "
                   << json_dicom_dataset.toStyledString() << ";";
            jsvm.run(streamstr.str(), jsvm.get_context());

            ++count;
        }
    }

    loggerDebug() << "Processing " << count << " DICOM files...";

    // Execute script
    std::string const script(
        "require('dicom2nifti/mr_image_storage.js');\n"
        "dicomifier.outputs = dicomifier.dicom2nifti.MRImageStorage(dicomifier.inputs);");
    jsvm.run(script, jsvm.get_context());

    // For each stack
    auto const length_value = jsvm.run(
        "dicomifier.outputs.length;", jsvm.get_context());
    auto const stack_number = length_value->ToInteger()->Value();
    int const nbdigit = 1 + floor(log10(stack_number));
    for (unsigned int stack_index = 0; stack_index < stack_number; ++stack_index)
    {
        // Get the JSON representation of the V8 data set.
        std::string json;
        {
            std::stringstream stream;
            stream << "JSON.stringify(dicomifier.outputs[" << stack_index << "]);";
            auto const value = jsvm.run(stream.str(), jsvm.get_context());
            json = *v8::String::Utf8Value(value);
        }

        // Parse it into a data set.
        Json::Value jsondataset;
        {
            Json::Reader reader;
            std::string old_locale = std::setlocale(LC_ALL, "C");
            reader.parse(json, jsondataset);
            std::setlocale(LC_ALL, old_locale.c_str());
        }

        // Write Nifti image file
        std::ostringstream prefix;
        prefix << std::setw(nbdigit) << std::setfill('0') << (stack_index+1);

        nifti_image * nim = extract_information_from_dataset(jsondataset,
                                                             prefix.str());
        nifti_image_write(nim);
        std::string filename(nim->iname);
        delete[] reinterpret_cast<uint8_t*>(nim->data);
        nim->data = 0; // if left pointing to data buffer
        // nifti_image_free will try and free this memory
        nifti_image_free(nim);

        // Write Metadata file
        boost::replace_all(filename, ".nii", ".json");
        jsondataset.removeMember("PixelData");
        std::ofstream myfile;
        myfile.open(filename);
        myfile << jsondataset.toStyledString();
        myfile.close();

    }

    loggerDebug() << "Done.";
}

nifti_image *
Dicom2Nifti
::extract_information_from_dataset(Json::Value const & dataset,
                                   std::string const & prefix) const
{
    // fill out the image header.
    nifti_image * nim = nifti_simple_init_nim();

    auto const seriesdesc = dataset.get("SeriesDescription", Json::Value());

    std::stringstream filename;
    filename << prefix << "_";
    if (!seriesdesc.isNull()) filename << seriesdesc[0].asString();
    filename << ".nii";

    // Get file name
    boost::filesystem::path const destination =
        boost::filesystem::path(this->_outputDir)
            /filename.str();
    boost::filesystem::create_directories(destination.parent_path());

    char * tempbasename = nifti_makebasename(destination.c_str());
    std::string const BaseName(tempbasename);
    free(tempbasename);

    nim->nifti_type = NIFTI_FTYPE_NIFTI1_1;

    nim->fname = nifti_makehdrname(BaseName.c_str(), nim->nifti_type, false, false);
    nim->iname = nifti_makeimgname(BaseName.c_str(), nim->nifti_type, false, false);

    // Initialize fields
    nim->nvox = 1;

    nim->xyz_units= static_cast< int >( NIFTI_UNITS_MM | NIFTI_UNITS_SEC );
    nim->dim[7] = nim->nw=1;
    nim->dim[6] = nim->nv=1;
    nim->dim[5] = nim->nu=1;
    nim->dim[4] = nim->nt=1;
    nim->dim[3] = nim->nz=1;
    nim->dim[2] = nim->ny=1;
    nim->dim[1] = nim->nx=1;

    // One stack = 3 dimensions
    nim->ndim = 3;
    nim->dim[0] = 3;

    // Get number of dataset in the stack
    unsigned int dsnumber = dataset.get("PixelData", Json::Value()).size();
    nim->dim[3] = nim->nz = dsnumber;
    nim->pixdim[3] = nim->dz = static_cast<float>( get_distance_between_slice(dataset) );
    nim->nvox *= nim->dim[3];

    nim->dim[2] = nim->ny = dataset.get("Columns", Json::Value())[0].asInt();
    nim->pixdim[2] = nim->dy = static_cast<float>( dataset.get("PixelSpacing", Json::Value())[1].asDouble() );
    nim->nvox *= nim->dim[2];

    nim->dim[1] = nim->nx = dataset.get("Rows", Json::Value())[0].asInt();
    nim->pixdim[1] = nim->dx = static_cast<float>( dataset.get("PixelSpacing", Json::Value())[0].asDouble() );
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
            dataset.get("ImageOrientationPatient", Json::Value());

    if (image_orientation_patient.isNull())
    {
        throw new DicomifierException("Missing ImageOrientationPatient");
    }

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

    /*mat44 matrix =
        nifti_make_orthog_mat44(directions[0],directions[3],directions[6],
                                directions[1],directions[4],directions[7],
                                -directions[2],-directions[5],-directions[8]);*/

    mat44 matrix2 =
        nifti_make_orthog_mat44(-directions[0],-directions[1],directions[2],
                                -directions[3],-directions[4],directions[5],
                                -directions[6],-directions[7],directions[8]);

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
            dataset.get("ImagePositionPatient", Json::Value());

    matrix.m[0][3] = static_cast<float>(-image_position_patient[0][0].asDouble());
    matrix.m[1][3] = static_cast<float>(-image_position_patient[0][1].asDouble());
    //NOTE:  The final dimension is not negated!
    matrix.m[2][3] = static_cast<float>( image_position_patient[0][2].asDouble());

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

double
Dicom2Nifti
::get_distance_between_slice(const Json::Value &dataset) const
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
