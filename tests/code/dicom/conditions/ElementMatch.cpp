#include <iostream>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/conditions/ElementMatch.h"
#include "dicom/actions/SetElement.h"

int main()
{
    DcmDataset * dataset = new DcmDataset();

    // Insert testing value
    router::actions::SetElement<EVR_CS>::New(dataset, DCM_Modality, "MyModality")->run();
    std::cout << "Insert MyModality into dataset" << std::endl;

    // Create conditions
    // Match Element and Value
    auto testOK1 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_Modality, "MyModality");
    // Match Element but not Value
    auto testKO1 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_Modality, "NotMyModality");
    // Match Value but not Element
    auto testKO2 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_PatientSex, "MyModality");
    // Match Nothing
    auto testKO3 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_PatientSex, "NotMyModality");
    
    // Test
    std::cout << "test ok 1: " << (testOK1->eval() ? "OK" : "KO") << std::endl;
    std::cout << "test ko 1: " << (testKO1->eval() ? "KO" : "OK") << std::endl;
    std::cout << "test ko 2: " << (testKO2->eval() ? "KO" : "OK") << std::endl;
    std::cout << "test ko 3: " << (testKO3->eval() ? "KO" : "OK") << std::endl;
    
    return EXIT_SUCCESS;
}
