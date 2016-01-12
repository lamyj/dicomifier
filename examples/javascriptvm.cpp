/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>
#include <sstream>

#include <odil/DataSet.h>
#include <odil/json_converter.h>
#include <odil/registry.h>

#include "lib/bruker/Dataset.h"
#include "lib/bruker/json_converter.h"
#include "lib/core/Logger.h"
#include "lib/javascript/JavascriptVM.h"

int main()
{
    dicomifier::InitializeLogger("DEBUG");

    dicomifier::javascript::JavascriptVM vm;

    // Create input
    std::stringstream streambruker;
    streambruker << "{ "
                 << "\"VisuSubjectName\" : [ \"S15-01\" ], "
                 << "\"VisuSubjectId\" : [ \"FLIIAM^S15-01\" ], "
                 << "\"VisuSubjectBirthDate\" : [ \"20150219\" ], "
                 << "\"VisuAcqRepetitionTime\" : [ 100 ], "
                 << "\"VisuCoreSize\" : [ 256, 256 ] }";

    Json::Value jsonbruker;
    streambruker >> jsonbruker;
    std::cout << "var jsonbruker = " << jsonbruker.toStyledString() << std::endl;

    std::stringstream stream;
    stream << "var inputs = [" << jsonbruker.toStyledString() << "];";
    auto result = vm.run(stream.str(), vm.get_context());

    // Create and execute script
    std::stringstream streamscript;
    streamscript << "var dataset = { }; "
                 << "dataset[\"00100010\"] = { \"vr\" : \"PN\", \"Value\" : [ { \"Alphabetic\" : inputs[0].VisuSubjectName[0] } ] };"
                 << "dataset[\"00100020\"] = { \"vr\" : \"LO\", \"Value\" : inputs[0].VisuSubjectId };"
                 << "dataset[\"00100030\"] = { \"vr\" : \"DA\", \"Value\" : inputs[0].VisuSubjectBirthDate };"
                 << "dataset[\"00180080\"] = { \"vr\" : \"DS\", \"Value\" : inputs[0].VisuAcqRepetitionTime };"
                 << "dataset[\"00280010\"] = { \"vr\" : \"US\", \"Value\" : [ inputs[0].VisuCoreSize[0] ] };"
                 << "dataset[\"00280011\"] = { \"vr\" : \"US\", \"Value\" : [ inputs[0].VisuCoreSize[1] ] };"
                 << "var outputs = [dataset];"
                 << "log(JSON.stringify(dataset));";
    auto result2 = vm.run(streamscript.str(), vm.get_context());

    // Retrieve output
    auto dicom_json = vm.run("JSON.stringify(outputs[0])", vm.get_context());
    v8::String::Utf8Value utf8(dicom_json);

    std::stringstream datasetstream;
    datasetstream << *utf8;
    Json::Value jsondataset;
    datasetstream >> jsondataset;
    std::cout << "jsondataset = " << jsondataset.toStyledString() << std::endl;
    odil::DataSet const dataset = odil::as_dataset(jsondataset);

    return EXIT_SUCCESS;
}
