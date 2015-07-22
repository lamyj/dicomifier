/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>
#include <sstream>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/json_converter.h>
#include <dcmtkpp/registry.h>

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
    streambruker << "{ \"VisuStudyId\" : [ \"FLIIAM^19022015\" ], "
                 << "\"VisuSubjectBirthDate\" : [ \"20150219\" ], "
                 << "\"VisuAcqRepetitionTime\" : [ 100 ], "
                 << "\"VisuCoreSize\" : [ 256, 256 ] }";

    Json::Value jsonbruker;
    streambruker >> jsonbruker;
    std::cout << "jsonbruker = " << jsonbruker.toStyledString() << std::endl;

    std::stringstream stream;
    stream << "inputs[0] = " << jsonbruker.toStyledString() << ";";
    auto result = vm.run(stream.str());

    // Create and execute script
    std::stringstream streamscript;
    streamscript << "var dataset = {}; "
                 << "dataset[\"00100020\"] = { \"vr\" : \"LO\", \"Value\" : inputs[0].VisuStudyId };"
                 << "dataset[\"00100030\"] = { \"vr\" : \"DA\", \"Value\" : inputs[0].VisuSubjectBirthDate };"
                 << "dataset[\"00180080\"] = { \"vr\" : \"DS\", \"Value\" : inputs[0].VisuAcqRepetitionTime };"
                 << "dataset[\"00280010\"] = { \"vr\" : \"US\", \"Value\" : [inputs[0].VisuCoreSize[0]] };"
                 << "dataset[\"00280011\"] = { \"vr\" : \"US\", \"Value\" : [inputs[0].VisuCoreSize[1]] };"
                 << "outputs[0] = dataset;"
                 << "log(JSON.stringify(dataset));";
    auto result2 = vm.run(streamscript.str());

    auto dicom_json = vm.run("JSON.stringify(outputs[0])");
    v8::String::Utf8Value utf8(dicom_json);

    std::stringstream datasetstream;
    datasetstream << *utf8;
    Json::Value jsondataset;
    datasetstream >> jsondataset;
    std::cout << "json = " << jsondataset.toStyledString() << std::endl;
    dcmtkpp::DataSet const dataset = dcmtkpp::as_dataset(jsondataset);

    return EXIT_SUCCESS;
}
