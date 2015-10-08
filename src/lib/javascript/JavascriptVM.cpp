/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <string>

#include <boost/filesystem.hpp>

#include <dcmtkpp/json_converter.h>
#include <dcmtkpp/Reader.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/Writer.h>

#include <nifti/nifti1_io.h>


#include "bruker/Directory.h"
#include "bruker/converters/EnhanceBrukerDicom.h"
#include "bruker/converters/pixel_data_converter.h"
#include "bruker/json_converter.h"
#include "core/DicomifierException.h"
#include "core/Logger.h"
#include "dicom/Dictionaries.h"
#include "JavascriptVM.h"
#include "LoggerJS.h"
#include "nifti/Dicom2Nifti.h"

namespace dicomifier
{

namespace javascript
{

void get_pixeldata_information(v8::Local<v8::Value> const & arg,
                               std::string & pixel_data,
                               std::string & word_type,
                               std::string & byte_order,
                               int & frame_size)
{
    // Get PIXELDATA
    if (!arg->ToObject()->Has(v8::String::New("PIXELDATA")))
    {
        throw DicomifierException("Missing pixel data path");
    }
    v8::Local<v8::Array> pixeldata =
            arg->ToObject()->Get(v8::String::New("PIXELDATA")).As<v8::Array>();
    v8::String::Utf8Value utf8pixeldata(pixeldata->Get(0)->ToString());
    std::stringstream pixel_data_stream;
    pixel_data_stream << *utf8pixeldata;

    pixel_data = pixel_data_stream.str();

    // Get VisuCoreWordType
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreWordType")))
    {
        throw DicomifierException(
                    "Missing mandatory Bruker field VisuCoreWordType");
    }
    v8::Local<v8::Array> wordtype =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreWordType")).As<v8::Array>();
    v8::String::Utf8Value utf8wordtype(wordtype->Get(0)->ToString());
    std::stringstream word_type_stream;
    word_type_stream << *utf8wordtype;

    word_type = word_type_stream.str();

    // Get VisuCoreByteOrder
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreByteOrder")))
    {
        throw DicomifierException(
                    "Missing mandatory Bruker field VisuCoreByteOrder");
    }
    v8::Local<v8::Array> byteorder =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreByteOrder")).As<v8::Array>();
    v8::String::Utf8Value utf8byteorder(byteorder->Get(0)->ToString());
    std::stringstream byte_order_stream;
    byte_order_stream << *utf8byteorder;

    byte_order = byte_order_stream.str();

    // Get VisuCoreSize
    if (!arg->ToObject()->Has(v8::String::New("VisuCoreSize")))
    {
        throw DicomifierException("Missing mandatory Bruker field VisuCoreSize");
    }
    v8::Local<v8::Array> coresize =
            arg->ToObject()->Get(
                v8::String::New("VisuCoreSize")).As<v8::Array>();
    frame_size = coresize->Get(0)->ToInt32()->Int32Value() *
                 coresize->Get(1)->ToInt32()->Int32Value();
}

/***********************************
 *  Exposed functions              *
 **********************************/

v8::Handle<v8::Value> is_big_endian(v8::Arguments const & args)
{
    return v8::Boolean::New(endian::is_big_endian());
}

v8::Handle<v8::Value> generate_uid(v8::Arguments const & args)
{
    char buffer[128];
    dcmGenerateUniqueIdentifier(buffer, SITE_INSTANCE_UID_ROOT);
    std::string const uid(buffer);
    return v8::String::New(uid.c_str());
}

/**
 * @brief Get pixel data as base64 String
 * @param args: 3 arguments:
 *              - BrukerDataset (JSON bruker dataset,
 *              - Number of Frame (int),
 *              - All_data (bool)
 * @return array of base64 String
 */
v8::Handle<v8::Value> load_pixel_data(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(v8::String::New("Missing BrukerDataset"));
    }
    if(args.Length() < 2)
    {
        return v8::ThrowException(v8::String::New("Missing frame number"));
    }

    v8::Local<v8::Value> const arg = args[0];

    std::string pixel_data;
    std::string word_type;
    std::string byte_order;
    int framesize;

    try
    {
        get_pixeldata_information(args[0], pixel_data, word_type, byte_order,
                                  framesize);
    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }

    // Get the frame number
    v8::Local<v8::Value> const argindex = args[1];
    auto numberOfFrame = argindex->ToInt32()->Int32Value();

    if (args.Length() == 3)
    {
        // Get a flag to return all pixel data or a string for each frame
        v8::Local<v8::Value> const argflag = args[2];
        bool flag_all_data = argflag->ToBoolean()->BooleanValue();

        if (flag_all_data)
        {
            framesize *= numberOfFrame;
            numberOfFrame = 1;
        }
    }

    // Create the array to return
    v8::Local<v8::Array> array = v8::Array::New(3);
    v8::Local<v8::Array> arrayimage = v8::Array::New(numberOfFrame);

    try
    {
        // Convert each frame in base64 String
        bruker::pixel_data_converter converter;
        for (unsigned int i = 0; i < numberOfFrame; ++i)
        {
            // Read pixel data file and get the Frame i
            dcmtkpp::DataSet dataset;
            converter(framesize, i, pixel_data, word_type, byte_order, dataset);

            // Convert to JSON
            Json::Value const json_dset = dcmtkpp::as_json(dataset);

            // Store into the array
            arrayimage->Set(i, v8::String::New(
                           json_dset["7fe00010"]["InlineBinary"].asCString()));
        }

        array->Set(0, arrayimage);
        array->Set(1, v8::Number::New(converter.get_rescaleintercept()));
        array->Set(2, v8::Number::New(converter.get_rescaleslope()));
    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch (std::exception const & otherexc)
    {
        return v8::ThrowException(v8::String::New(otherexc.what()));
    }

    return array;
}

v8::Handle<v8::Value> sort_pixel_data(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(v8::String::New("Missing input"));
    }

    try
    {
        std::string pixel_data;
        std::string word_type;
        std::string byte_order;
        int framesize;
        get_pixeldata_information(args[0], pixel_data, word_type, byte_order,
                                  framesize);

        v8::Local<v8::Array> array = args[1].As<v8::Array>();

        dcmtkpp::Element element = dcmtkpp::Element(dcmtkpp::Value::Binary(),
                                                    dcmtkpp::VR::OW);
        bruker::pixel_data_converter converter;
        for (unsigned int i = 0; i < array->Length(); ++i)
        {
            int index = array->Get(i)->ToInt32()->Int32Value();
            dcmtkpp::DataSet dataset;
            converter(framesize, index, pixel_data, word_type,
                      byte_order, dataset);

            auto temp = dataset.as_binary(dcmtkpp::registry::PixelData);
            element.as_binary().insert(element.as_binary().end(),
                                       temp.begin(), temp.end());
        }

        dcmtkpp::DataSet dataset;
        dataset.add(dcmtkpp::registry::PixelData, element);

        // Convert to JSON
        Json::Value const json_dtset = dcmtkpp::as_json(dataset);

        return v8::String::New(
                    json_dtset["7fe00010"]["InlineBinary"].asCString());

    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch (std::exception const & otherexc)
    {
        return v8::ThrowException(v8::String::New(otherexc.what()));
    }
    return v8::Null();
}

/**
 * @brief generate_dicom_filename
 * @param args
 * @return
 */
v8::Handle<v8::Value> generate_dicom_filename(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(v8::String::New("Missing input"));
    }

    v8::Local<v8::Object> object = args[0].As<v8::Object>();

    auto const outputdir_js = object->Get(v8::String::New("outputDir"))->ToString();
    std::string outputdir(outputdir_js->Utf8Length(), '\0');
    outputdir_js->WriteUtf8(&outputdir[0]);

    auto const studyNumber_js = object->Get(v8::String::New("studyNumber"))->ToString();
    std::string studyNumber(studyNumber_js->Utf8Length(), '\0');
    studyNumber_js->WriteUtf8(&studyNumber[0]);

    auto const seriesNumber_js = object->Get(v8::String::New("seriesNumber"))->ToString();
    std::string seriesNumber(seriesNumber_js->Utf8Length(), '\0');
    seriesNumber_js->WriteUtf8(&seriesNumber[0]);

    std::string subject_name;
    if (object->Get(v8::String::New("SubjectName")).IsEmpty())
    {
        subject_name = bruker::EnhanceBrukerDicom::get_default_directory_name(outputdir);
    }
    else
    {
        auto const subjectname_js = object->Get(v8::String::New("SubjectName"))->ToString();
        std::string subjectname(subjectname_js->Utf8Length(), '\0');
        subjectname_js->WriteUtf8(&subjectname[0]);

        subject_name = subjectname;
    }

    auto const StudyDescription_js = object->Get(v8::String::New("StudyDescription"))->ToString();
    std::string StudyDescription(StudyDescription_js->Utf8Length(), '\0');
    StudyDescription_js->WriteUtf8(&StudyDescription[0]);

    auto const SeriesDescription_js = object->Get(v8::String::New("SeriesDescription"))->ToString();
    std::string SeriesDescription(SeriesDescription_js->Utf8Length(), '\0');
    SeriesDescription_js->WriteUtf8(&SeriesDescription[0]);

    // Study Directory: Counter + Study Description
    auto const study = bruker::EnhanceBrukerDicom::create_directory_name(
            8, studyNumber, StudyDescription);

    // Series Directory: Bruker Series directory + Series Description
    auto series_number = seriesNumber.substr(0, seriesNumber.size() == 6 ? 2 : 1);
    auto const series = bruker::EnhanceBrukerDicom::create_directory_name(
        8, series_number, SeriesDescription);

    // Instance file: Instance Number
    std::string instance = "1";
    if (object->Get(v8::String::New("useFileFormat"))->ToBoolean()->BooleanValue())
    {
        auto const instance_number = object->Get(v8::String::New("InstanceNumber"))->ToInt32()->Int32Value();

        auto const images_in_acquistion = object->Get(v8::String::New("ImagesInAcquisition"))->ToInt32()->Int32Value();

        int const nbdigit = 1 + floor(log10(images_in_acquistion));

        std::ostringstream stream;
        stream << std::setw(nbdigit) << std::setfill('0') << instance_number;
        instance = stream.str();
    }

    // Destination: Subject/Study/Series/Instance
    boost::filesystem::path const destination =
        boost::filesystem::path(outputdir)
            /subject_name.c_str()/study/series/instance;
    boost::filesystem::create_directories(destination.parent_path());

    return v8::String::New(destination.c_str());
}

/**
 * @brief read_bruker_directory
 * @param args[0]: bruker directory path
 * @param args[1]: Series Number
 * @return Bruker Dataset as JSON representation
 */
v8::Handle<v8::Value> read_bruker_directory(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(
                v8::String::New("Missing Arguments for readBrukerDirectory"));
    }

    auto const bruker_path_js = args[0]->ToString();
    std::string bruker_path(bruker_path_js->Utf8Length(), '\0');
    bruker_path_js->WriteUtf8(&bruker_path[0]);

    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(bruker_path) )
    {
        std::stringstream error;
        error << "Input not a Directory: " << bruker_path;
        return v8::ThrowException(v8::String::New(error.str().c_str()));
    }

    try
    {
        // Parse input bruker directory
        bruker::Directory bruker_directory;
        bruker_directory.load(bruker_path);

        auto const series_number_js = args[1]->ToString();
        std::string series_number(series_number_js->Utf8Length(), '\0');
        series_number_js->WriteUtf8(&series_number[0]);

        // Search corresponding Bruker Dataset
        if(!bruker_directory.has_dataset(series_number))
        {
            return v8::ThrowException(v8::String::New("No such series"));
        }

        auto const & brukerdataset = bruker_directory.get_dataset(series_number);

        auto const json_bruker_dataset = dicomifier::bruker::as_json(brukerdataset);

        std::stringstream script;
        script << "var bruker = "
               << bruker::as_string(json_bruker_dataset) << ";\n" << "bruker;";

        return JavascriptVM::run(script.str(), v8::Context::GetCurrent());
    }
    catch (dicomifier::DicomifierException const & dcexc)
    {
        return v8::ThrowException(v8::String::New(dcexc.what()));
    }
    catch (dcmtkpp::Exception const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

/**
 * @brief read_dicom
 * @param args[0]: DICOM file path
 * @return DICOM dataset as JSON representation
 */
v8::Handle<v8::Value> read_dicom(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::ThrowException(
                v8::String::New("Missing input DICOM file path"));
    }

    auto const filename = args[0]->ToString();
    std::string filename_utf8(filename->Utf8Length(), '\0');
    filename->WriteUtf8(&filename_utf8[0]);

    std::ifstream stream(boost::filesystem::path(filename_utf8).c_str(),
                         std::ios::in | std::ios::binary);

    std::pair<dcmtkpp::DataSet, dcmtkpp::DataSet> file;
    try
    {
        file = dcmtkpp::Reader::read_file(stream);
    }
    catch(std::exception const & e)
    {
        dicomifier::loggerError() << "Could not read '" << filename_utf8
                                  << "': " << e.what() << "\n";
        return v8::Null();
    }

    if (!file.second.has(dcmtkpp::registry::PixelData))
    {
        // ignore file
        return v8::Null();
    }

    try
    {
        auto const json_dicom_dataset = dcmtkpp::as_json(file.second);

        std::stringstream script;
        script << "var dicom = "
               << json_dicom_dataset.toStyledString() << ";\n" << "dicom;";

        return JavascriptVM::run(script.str(), v8::Context::GetCurrent());
    }
    catch (dicomifier::DicomifierException const & dcexc)
    {
        return v8::ThrowException(v8::String::New(dcexc.what()));
    }
    catch (dcmtkpp::Exception const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch(std::exception const & e)
    {
        return v8::ThrowException(v8::String::New(e.what()));
    }

    return v8::Null();
}

/**
 * @brief write_nifti
 * @param args[0]: DICOM dataset as JSON representation
 * @param args[1]: dimension of output NIfTI (3D or 4D)
 * @param args[2]: NIfTI file name (image)
 * @param args[3]: JSON file name (metadata)
 * @return NULL if no error occured
 */
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

    nifti::NIfTI_Dimension dimension =
            (nifti::NIfTI_Dimension)args[1]->ToInt32()->Int32Value();

    // Write Nifti image file
    auto const path_nii_js = args[2]->ToString();
    std::string path_nii_utf8(path_nii_js->Utf8Length(), '\0');
    path_nii_js->WriteUtf8(&path_nii_utf8[0]);

    boost::filesystem::path const destination =
        boost::filesystem::path(path_nii_utf8);
    boost::filesystem::create_directories(destination.parent_path());

    nifti_image * nim = nifti::Dicom2Nifti::
            extract_information_from_dataset(jsondataset,
                                             path_nii_utf8, dimension);
    nifti_image_write(nim);
    delete[] reinterpret_cast<uint8_t*>(nim->data);
    nim->data = 0; // if left pointing to data buffer
    // nifti_image_free will try and free this memory
    nifti_image_free(nim);

    // Write Metadata file
    auto const path_json_js = args[3]->ToString();
    std::string path_json_utf8(path_json_js->Utf8Length(), '\0');
    path_json_js->WriteUtf8(&path_json_utf8[0]);

    boost::filesystem::path const destinationjson =
        boost::filesystem::path(path_json_utf8);
    boost::filesystem::create_directories(destinationjson.parent_path());

    jsondataset.removeMember("PixelData");
    jsondataset.removeMember("DICOMIFIER_STACKS_NUMBER");
    jsondataset.removeMember("DICOMIFIER_DATASET_PERSTACK_NUMBER");
    std::ofstream myfile;
    myfile.open(path_json_utf8);
    myfile << jsondataset.toStyledString();
    myfile.close();
    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch (std::exception const & otherexc)
    {
        return v8::ThrowException(v8::String::New(otherexc.what()));
    }

    return v8::Null();
}

/**
 * @brief write_dicom
 * @param args[0]: DICOM dataset as JSON representation
 * @param args[1]: DICOM file path
 * @param args[2]: Transfer Syntax
 * @return NULL if no error occured
 */
v8::Handle<v8::Value> write_dicom(v8::Arguments const & args)
{
    if(args.Length() < 2)
    {
        return v8::ThrowException(
                v8::String::New("Missing Arguments for writeDICOM"));
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

        auto const dataset = dcmtkpp::as_dataset(jsondataset);

        // Get output file name
        auto const path_dcm_js = args[1]->ToString();
        std::string path_dcm_utf8(path_dcm_js->Utf8Length(), '\0');
        path_dcm_js->WriteUtf8(&path_dcm_utf8[0]);

        // Create directory if not exist
        boost::filesystem::path const destination =
            boost::filesystem::path(path_dcm_utf8);
        boost::filesystem::create_directories(destination.parent_path());

        std::string transfer_syntax = dcmtkpp::registry::ExplicitVRLittleEndian;
        if(args.Length() == 3)
        {
            auto const tsyntax_js = args[2]->ToString();
            std::string tsyntax_utf8(tsyntax_js->Utf8Length(), '\0');
            tsyntax_js->WriteUtf8(&tsyntax_utf8[0]);

            transfer_syntax = tsyntax_utf8;
        }

        std::stringstream stream;
        dcmtkpp::Writer::write_file(
                    dataset, stream, transfer_syntax,
                    dcmtkpp::Writer::ItemEncoding::UndefinedLength, false);

        std::ofstream outputstream(destination.c_str(),
                                   std::ios::out | std::ios::binary);
        outputstream << stream.str();
        outputstream.close();
    }
    catch (DicomifierException const & exc)
    {
        return v8::ThrowException(v8::String::New(exc.what()));
    }
    catch (dcmtkpp::Exception const & dcmtkppexc)
    {
        return v8::ThrowException(v8::String::New(dcmtkppexc.what()));
    }
    catch (std::exception const & otherexc)
    {
        return v8::ThrowException(v8::String::New(otherexc.what()));
    }

    return v8::Null();
}

v8::Handle<v8::Value> namespace_(v8::Arguments const & args)
{
    auto const path_js = args[0]->ToString();
    std::string path_utf8(path_js->Utf8Length(), '\0');
    path_js->WriteUtf8(&path_utf8[0]);

    v8::HandleScope scope;
    v8::Handle<v8::Object> ns = v8::Context::GetCurrent()->Global();

    std::istringstream stream(path_utf8);
    std::string item;

    while(std::getline(stream, item, '.'))
    {
        v8::Local<v8::String> item_js = v8::String::New(item.c_str());

        v8::Local<v8::Object> child;
        if(!ns->Has(item_js))
        {
            child = v8::Object::New();
            ns->Set(item_js, child);
        }
        else
        {
            child = ns->Get(item_js)->ToObject();
        }

        ns = child;
    }


    return scope.Close(ns);
}

v8::Handle<v8::Value> require(v8::Arguments const & args)
{
    auto const path_js = args[0]->ToString();
    std::string path_utf8(path_js->Utf8Length(), '\0');
    path_js->WriteUtf8(&path_utf8[0]);

    boost::filesystem::path absolute_path;
    // 1. The directory containing the current file
    if(boost::filesystem::is_regular(boost::filesystem::current_path()/path_utf8))
    {
        absolute_path = boost::filesystem::current_path()/path_utf8;
    }
    // 2. The paths listed in DICOMIFIER_JS_PATH (environment variable)
    else if(absolute_path.empty() && getenv("DICOMIFIER_JS_PATH") != NULL)
    {
        boost::filesystem::path const root(getenv("DICOMIFIER_JS_PATH"));
        if(boost::filesystem::is_regular(root/path_utf8))
        {
            absolute_path = root/path_utf8;
        }
    }
    // 3. The path listed in DICOMIFIER_DEFAULT_JS_PATH (compiler symbol)
#ifdef DICOMIFIER_DEFAULT_JS_PATH
    else if(absolute_path.empty())
    {
        boost::filesystem::path const root(DICOMIFIER_DEFAULT_JS_PATH);
        if(boost::filesystem::is_regular(root/path_utf8))
        {
            absolute_path = root/path_utf8;
        }
    }
#endif

    if(absolute_path.empty())
    {
        return v8::ThrowException(
                    v8::String::New(("No such file: "+path_utf8).c_str()));
    }

    auto const context = v8::Context::GetCurrent();
    return JavascriptVM::run_file(absolute_path.generic_string(), context);
}

/***********************************
 **********************************/

JavascriptVM
::JavascriptVM()
{
    // Create a new Isolate and make it the current one.
    this->_isolate = v8::Isolate::New();
    {

    /**********************************
     * Create all required structures *
     **********************************/

    //v8::Isolate::Scope isolate_scope(this->_isolate);
    v8::HandleScope handle_scope;

    auto global = v8::ObjectTemplate::New();

    // Create a new context.
    // Context must be ready before creating an array
    // cf. https://stackoverflow.com/questions/7015068/why-does-creating-new-v8array-before-v8scope-cause-segmentation-fault-but-v

    this->_context = v8::Context::New(NULL, global);
    v8::Context::Scope context_scope(this->_context);

    /**************************
     * Fill the global object *
     **************************/

#define DICOMIFIER_EXPOSE_FUNCTION(cpp_name, js_name) \
    this->_context->Global()->Set(\
        v8::String::New(js_name), \
        v8::FunctionTemplate::New(cpp_name)->GetFunction());

    DICOMIFIER_EXPOSE_FUNCTION(log, "log");
    DICOMIFIER_EXPOSE_FUNCTION(is_big_endian, "bigEndian");
    DICOMIFIER_EXPOSE_FUNCTION(load_pixel_data, "loadPixelData");
    DICOMIFIER_EXPOSE_FUNCTION(sort_pixel_data, "sortPixelData");
    DICOMIFIER_EXPOSE_FUNCTION(generate_dicom_filename, "generateDICOMFileName");
    DICOMIFIER_EXPOSE_FUNCTION(read_bruker_directory, "readBrukerDirectory");
    DICOMIFIER_EXPOSE_FUNCTION(read_dicom, "readDICOM");
    DICOMIFIER_EXPOSE_FUNCTION(write_nifti, "writeNIfTI");
    DICOMIFIER_EXPOSE_FUNCTION(write_dicom, "writeDICOM");
    DICOMIFIER_EXPOSE_FUNCTION(generate_uid, "dcmGenerateUniqueIdentifier");
    DICOMIFIER_EXPOSE_FUNCTION(require, "require");
    DICOMIFIER_EXPOSE_FUNCTION(namespace_, "namespace");

#undef DICOMIFIER_EXPOSE_FUNCTION

    auto myobject = v8::Object::New();
    myobject->Set(v8::String::New("inputs"), v8::Array::New());
    myobject->Set(v8::String::New("outputs"), v8::Array::New());

    this->_context->Global()->Set(
        v8::String::New("dicomifier"),
        myobject);
    }

    std::stringstream streamdictionary;
    streamdictionary << "dicomifier[\"dictionary\"] = "
                     << Dictionaries::public_dictionary_as_json()
                     << ";";
    JavascriptVM::run(streamdictionary.str(), this->get_context());
}

JavascriptVM
::~JavascriptVM()
{
    this->_isolate->Dispose();
}

v8::Handle<v8::Context>
JavascriptVM
::get_context() const
{
    return this->_context;
}

v8::Local<v8::Value>
JavascriptVM
::run(std::string const & source, v8::Handle<v8::Context> const & context)
{
    v8::Context::Scope context_scope(context);

    v8::HandleScope handle_scope;
    v8::TryCatch try_catch;

    auto const source_js = v8::String::New(source.c_str());
    auto const script = v8::Script::Compile(source_js);
    if(script.IsEmpty())
    {
        std::ostringstream message;
        message << "Line " << try_catch.Message()->GetLineNumber() << ": "
            << *v8::String::AsciiValue(try_catch.Exception());
        throw dicomifier::DicomifierException(message.str());
    }

    auto const result = script->Run();
    if(result.IsEmpty())
    {
        std::ostringstream message;
        message << "Line " << try_catch.Message()->GetLineNumber() << ": "
            << *v8::String::AsciiValue(try_catch.Exception());
        throw dicomifier::DicomifierException(message.str());
    }

    return result;
}

v8::Local<v8::Value>
JavascriptVM
::run_file(std::string const & scriptpath, v8::Handle<v8::Context> const & context)
{
    // Open file
    std::ifstream streamfile(scriptpath.c_str(), std::ifstream::binary);

    // Get file size
    streamfile.seekg(0, streamfile.end);
    auto const size = streamfile.tellg();
    streamfile.seekg(0, streamfile.beg);

    // Read file
    std::string buffer;
    buffer.resize(size);
    streamfile.read((char*)(&buffer[0]), size);

    // Close file
    streamfile.close();

    // Execute script
    return JavascriptVM::run(buffer, context);
}

} // namespace javascript

} // namespace dicomifier
