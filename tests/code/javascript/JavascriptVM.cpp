/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleJavascriptVM
#include <boost/test/unit_test.hpp>

#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>
#include <v8.h>

#include "core/DicomifierException.h"
#include "core/Endian.h"
#include "javascript/JavascriptVM.h"

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    dicomifier::javascript::JavascriptVM * vm =
            new dicomifier::javascript::JavascriptVM();

    BOOST_REQUIRE(vm != NULL);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Run script
 */
BOOST_AUTO_TEST_CASE(Run)
{
    dicomifier::javascript::JavascriptVM vm;

    v8::Local<v8::Value> result = vm.run(
        "JSON.stringify({ 'hello' : 'world' });", vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream stream;
    stream << *utf8;

    BOOST_CHECK_EQUAL("{\"hello\":\"world\"}", stream.str());
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Run script file
 */
struct TestDataRunFile
{
    std::string filename;

    TestDataRunFile():
        filename("./tmp_test_moduleJavaScriptVM.js")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "JSON.stringify({ 'hello' : 'world' });\n";
        myfile.close();
    }

    ~TestDataRunFile()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunFile, TestDataRunFile)
{
    dicomifier::javascript::JavascriptVM vm;

    v8::Local<v8::Value> result = vm.run_file(filename, vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream stream;
    stream << *utf8;

    BOOST_CHECK_EQUAL("{\"hello\":\"world\"}", stream.str());
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Require local JS file
 */
BOOST_FIXTURE_TEST_CASE(Require, TestDataRunFile)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream script;
    script << "require(\"" << filename << "\");";

    // Require no error
    v8::Local<v8::Value> result = vm.run(script.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream stream;
    stream << *utf8;

    BOOST_CHECK_EQUAL("{\"hello\":\"world\"}", stream.str());
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: is_big_endian
 */
BOOST_AUTO_TEST_CASE(Function_isBigEndian)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "bigEndian();";

    v8::Local<v8::Value> result = vm.run(streaminput.str(), vm.get_context());
    BOOST_REQUIRE_EQUAL(result->ToBoolean()->BooleanValue(),
                        dicomifier::is_big_endian());
    BOOST_REQUIRE_EQUAL(result->ToBoolean()->BooleanValue(),
                        !dicomifier::is_little_endian());
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: generate_uid
 */
BOOST_AUTO_TEST_CASE(Function_generateUID)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "dcmGenerateUniqueIdentifier();";

    v8::Local<v8::Value> result = vm.run(streaminput.str(), vm.get_context());

    auto const uid = result->ToString();
    std::string uid_utf8(uid->Utf8Length(), '\0');
    uid->WriteUtf8(&uid_utf8[0]);

    BOOST_REQUIRE_NE(uid_utf8, "");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function dictionaryMapper descibes into function.js
 */
BOOST_AUTO_TEST_CASE(Functions_dictionaryMapper)
{
    dicomifier::javascript::JavascriptVM vm;

    std::map<std::string, std::string> const testedvalues =
            { { "first", "hello" }, { "second", "world" } };

    std::string const dict =
            "var dictionary = { 'first': 'hello', 'second': 'world' };";

    typedef std::map<std::string, std::string>::const_iterator const_iterator;
    for (const_iterator it = testedvalues.begin();
         it != testedvalues.end(); ++it)
    {
        std::stringstream streaminput;
        streaminput << "require('bruker2dicom/common.js');\n";
        streaminput << dict << "String(['" << it->first
                    << "'].map(dicomifier.bruker2dicom.dictionaryMapper(dictionary)));";

        v8::Local<v8::Value> result = vm.run(streaminput.str(), vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream stream;
        stream << *utf8;

        BOOST_CHECK_EQUAL(it->second, stream.str());
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function dateTimeMapper descibes into function.js
 */
BOOST_AUTO_TEST_CASE(Functions_dateTimeMapper)
{
    dicomifier::javascript::JavascriptVM vm;

    std::map<std::string, std::string> const testedvalues =
            { { "date", "20150219" }, { "time", "085940" } };

    typedef std::map<std::string, std::string>::const_iterator const_iterator;
    for (const_iterator it = testedvalues.begin();
         it != testedvalues.end(); ++it)
    {
        std::stringstream streaminput;
        streaminput << "require('bruker2dicom/common.js');\n";
        streaminput << "var array = [ '2015-02-19T09:59:40,234+0100' ];"
                    << "String(array.map(dicomifier.bruker2dicom.dateTimeMapper('"
                    << it->first << "')));";

        v8::Local<v8::Value> result = vm.run(streaminput.str(), vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream stream;
        stream << *utf8;

        BOOST_CHECK_EQUAL(it->second, stream.str());
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
struct TestDataToDicom
{
    dicomifier::javascript::JavascriptVM vm;
    std::stringstream streamscript;

    TestDataToDicom()
    {
        // Create input
        std::stringstream streambruker;
        streambruker << "{ "
                     << "\"VisuCoreFrameCount\": [ \"3\" ],"
                     << "\"VisuCoreSize\": [ 256, 256 ],"
                     << "\"VisuSubjectId\" : [ \"MySubjectID\" ],"
                     << "\"VisuSubjectName\" : [ \"MyName\" ],"
                     << "\"VisuSubjectSex\" : [ \"MALE\" ],"
                     << "\"VisuExperimentNumber\": [ \"1\" ],"
                     << "\"VisuFGOrderDesc\": [[3, \"FG_SLICE\", \"\", 0, 2]],"
                     << "\"VisuFGOrderDescDim\": [ \"1\" ],"
                     << "\"VisuGroupDepVals\": [[ \"VisuCoreOrientation\", 0 ],"
                     << "[ \"VisuCorePosition\", 0 ]]"
                     << "}";

        Json::Value jsonbruker;
        streambruker >> jsonbruker;

        std::stringstream stream;
        stream << "dicomifier.inputs[0] = "
               << jsonbruker.toStyledString() << ";";

        vm.run(stream.str(), vm.get_context());

        streamscript << "require('bruker2dicom/common.js');\n"
                     << "require('bruker2dicom/frame_index_generator.js');\n"
                     << "var dataset = {}; "
                     << "var brukerDataset = dicomifier.inputs[0]; "
                     << "var frameGroups = "
                     <<     "dicomifier.bruker2dicom.getFrameGroups(brukerDataset); "
                     << "var indexGenerator = "
                     <<     "new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups); ";
    }

    ~TestDataToDicom()
    {

    }
};

BOOST_FIXTURE_TEST_CASE(Functions_toDicom, TestDataToDicom)
{
    for (unsigned int i = 1; i < 4; ++i)
    {
        std::stringstream stream;
        stream << streamscript.str()
               << "require('bruker2dicom/common.js');\n"
               << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientID', "
               <<         "brukerDataset, 'VisuSubjectId', " << i << "); "
               << "JSON.stringify(dataset);";

        auto result = vm.run(stream.str(), vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream datasetstream;
        datasetstream << *utf8;

        BOOST_CHECK_EQUAL(
                datasetstream.str(),
                "{\"00100020\":{\"vr\":\"LO\",\"Value\":[\"MySubjectID\"]}}");
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_NoValue, TestDataToDicom)
{
    // Type = 1: see test Functions_toDicom_NoValue_type1
    // Type = 2
    {
        std::stringstream stream;
        stream << streamscript.str()
               << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientID', "
               <<         "brukerDataset, null, 2); "
               << "JSON.stringify(dataset);";

        auto result = vm.run(stream.str(), vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream datasetstream;
        datasetstream << *utf8;

        BOOST_CHECK_EQUAL(datasetstream.str(), "{\"00100020\":{\"vr\":\"LO\"}}");
    }
    // Type = 3
    {
        std::stringstream stream;
        stream << streamscript.str()
               << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientID', "
               <<         "brukerDataset, null, 3); "
               << "JSON.stringify(dataset);";

        auto result = vm.run(stream.str(), vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream datasetstream;
        datasetstream << *utf8;

        BOOST_CHECK_EQUAL(datasetstream.str(), "{}");
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_PN, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientName', "
           <<         "brukerDataset, 'VisuSubjectName', 2); "
           << "JSON.stringify(dataset);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream datasetstream;
    datasetstream << *utf8;

    BOOST_CHECK_EQUAL(datasetstream.str(),
      "{\"00100010\":{\"vr\":\"PN\",\"Value\":[{\"Alphabetic\":\"MyName\"}]}}");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_Setter, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 2, "
           <<         "dicomifier.bruker2dicom.dictionaryMapper({'MALE': 'M', 'FEMALE': 'F',"
           <<                           "'UNDEFINED': 'O', 'UNKNOWN': 'O' })); "
           << "JSON.stringify(dataset);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream datasetstream;
    datasetstream << *utf8;

    BOOST_CHECK_EQUAL(
                datasetstream.str(),
                "{\"00100040\":{\"vr\":\"CS\",\"Value\":[\"M\"]}}");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_Getter, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 2, undefined, "
           <<         "function(brukerDS) { return ['F']; }); "
           << "JSON.stringify(dataset);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream datasetstream;
    datasetstream << *utf8;

    BOOST_CHECK_EQUAL(
                datasetstream.str(),
                "{\"00100040\":{\"vr\":\"CS\",\"Value\":[\"F\"]}}");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Test function toDicom descibes into function.js
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_NullValue, TestDataToDicom)
{
    // type 1: see test Functions_toDicom_NullValueType1
    // type 2
    {
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 2, undefined, "
           <<         "function(brukerDS) { return null; }); "
           << "JSON.stringify(dataset);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream datasetstream;
    datasetstream << *utf8;

    BOOST_CHECK_EQUAL(
                datasetstream.str(),
                "{\"00100040\":{\"vr\":\"CS\"}}");
    }
    // type 3
    {
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 3, undefined, "
           <<         "function(brukerDS) { return null; }); "
           << "JSON.stringify(dataset);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream datasetstream;
    datasetstream << *utf8;

    BOOST_CHECK_EQUAL(
                datasetstream.str(),
                "{\"00100040\":{\"vr\":\"CS\"}}");
    }
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Generate an exception
 */
BOOST_AUTO_TEST_CASE(Exception)
{
    dicomifier::javascript::JavascriptVM vm;

    BOOST_REQUIRE_THROW(
        vm.run("throw new dicomifier.Exception('my fault');", vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Generate an exception
 */
BOOST_AUTO_TEST_CASE(run_empty_script)
{
    dicomifier::javascript::JavascriptVM vm;

    BOOST_REQUIRE_THROW(
        vm.run("my error", vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: No such file
 */
BOOST_AUTO_TEST_CASE(no_such_js_file)
{
    dicomifier::javascript::JavascriptVM vm;

    BOOST_REQUIRE_THROW(
        vm.run("require('unknown_file.js');", vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function dictionaryMapper descibes into function.js
 *                  Unknown value
 */
BOOST_AUTO_TEST_CASE(Functions_dictionaryMapper_UnknownValue)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "var dictionary = { 'first': 'hello', 'second': 'world' };"
                << "String(['UnknownValue'].map(dictionaryMapper(dictionary)));";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function dateTimeMapper descibes into function.js
 *                  Unknown format
 */
BOOST_AUTO_TEST_CASE(Functions_dateTimeMapper_UnknownFormat)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "var array = [ '2015-02-19T09:59:40,234+0100' ];"
                << "String(array.map(dateTimeMapper('Unknown')));";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function toDicom descibes into function.js
 *                  No value for Type 1
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_NoValue_type1, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientID', "
           <<         "brukerDataset, null, 1); "
           << "JSON.stringify(dataset);";

    BOOST_REQUIRE_THROW(
        vm.run(stream.str(), vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function toDicom descibes into function.js
 *                  Unknown type
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_UnknownType, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientID', "
           <<         "brukerDataset, null, 9); "
           << "JSON.stringify(dataset);";

    BOOST_REQUIRE_THROW(
        vm.run(stream.str(), vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function toDicom descibes into function.js
 *                  Unknown DICOM tag
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_UnknownDicomTag, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'UnknownTag', "
           <<         "brukerDataset, null, 1); "
           << "JSON.stringify(dataset);";

    BOOST_REQUIRE_THROW(
        vm.run(stream.str(), vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function toDicom descibes into function.js
 *                  Null value and type 1
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_NullValueType1, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 1, undefined, "
           <<         "function(brukerDS) { return null; }); "
           << "JSON.stringify(dataset);";

    BOOST_REQUIRE_THROW(
        vm.run(stream.str(), vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function toDicom descibes into function.js
 *                  Empty value and type 1
 */
BOOST_FIXTURE_TEST_CASE(Functions_toDicom_EmptyValueType1, TestDataToDicom)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "dicomifier.bruker2dicom.toDicom(indexGenerator, dataset, 'PatientSex', "
           <<         "brukerDataset, 'VisuSubjectSex', 1, undefined, "
           <<         "function(brukerDS) { return []; }); "
           << "JSON.stringify(dataset);";

    BOOST_REQUIRE_THROW(
        vm.run(stream.str(), vm.get_context()),
        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function load_pixel_data
 *                  Bruker DataSet missing
 */
BOOST_AUTO_TEST_CASE(Function_loadPixelData_no_dataset)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "loadPixelData();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function load_pixel_data
 *                  Frame number missing
 */
BOOST_AUTO_TEST_CASE(Function_loadPixelData_no_frameNumber)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "loadPixelData({});";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function load_pixel_data
 *                  PixelData missing
 */
BOOST_AUTO_TEST_CASE(Function_loadPixelData_no_pixelData)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "loadPixelData({}, 1);";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function load_pixel_data
 *                  VisuCoreByteOrder missing
 */
BOOST_AUTO_TEST_CASE(Function_loadPixelData_no_VisuCoreByteOrder)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "loadPixelData({ \"PIXELDATA\" : [ \"value\" ], "
                << "\"VisuCoreWordType\" : [ \"value\" ] }, 1);";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function sort_pixel_data
 *                  Input missing
 */
BOOST_AUTO_TEST_CASE(Function_sortPixelData_no_Input)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "sortPixelData();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function sort_pixel_data
 *                  Pixel data missing
 */
BOOST_AUTO_TEST_CASE(Function_sortPixelData_MissingPixelData)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "sortPixelData({}, []);";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function read_dicom
 *                  DICOM file missing
 */
BOOST_AUTO_TEST_CASE(Function_readDicom_no_DICOMFile)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "readDICOM();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function write_nifti
 *                  arguments missing
 */
BOOST_AUTO_TEST_CASE(Function_writeNIfTI_missingArgs)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "writeNIfTI();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function generate_dicom_filename
 *                  arguments missing
 */
BOOST_AUTO_TEST_CASE(Function_generateDICOMFileName_missingArgs)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "generateDICOMFileName();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function read_bruker_directory
 *                  arguments missing
 */
BOOST_AUTO_TEST_CASE(Function_readBrukerDirectory_missingArgs)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "readBrukerDirectory();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Test function write_dicom
 *                  arguments missing
 */
BOOST_AUTO_TEST_CASE(Function_writeDICOM_missingArgs)
{
    dicomifier::javascript::JavascriptVM vm;

    std::stringstream streaminput;
    streaminput << "writeDICOM();";

    BOOST_REQUIRE_THROW(vm.run(streaminput.str(), vm.get_context()),
                        dicomifier::DicomifierException);
}
