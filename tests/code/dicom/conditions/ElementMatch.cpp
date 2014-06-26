#include <iostream>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/conditions/ElementMatch.h"

int main()
{
    DcmDataset * dataset = new DcmDataset();  

    // Insert testing value
    DcmElement * element = NULL;
    std::string test = "value1\\value2\\value3";
    dataset->putAndInsertOFStringArray(DCM_Modality, test.c_str());     // insert CS
    dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60");        // insert DS
    dataset->putAndInsertOFStringArray(DCM_StageNumber, "12");          // insert IS
    
    // Create conditions
    // Match Element and Value (CS)
    auto testOK1 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_Modality, {"value1", "value2", "value3"});
    // Match Element but not Value (CS)
    auto testKO1 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_Modality, {"value1", "badValue", "value3"});
    // Match Value but not Element (CS)
    auto testKO2 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_PatientSex, {"value1", "value2", "value3"});
    // Match Nothing (CS)
    auto testKO3 = router::conditions::ElementMatch<EVR_CS>::New(dataset, DCM_PatientSex, {"value1", "badValue", "value3"});
    // Match Element and Value (DS)
    auto testOK2 = router::conditions::ElementMatch<EVR_DS>::New(dataset, DCM_PatientWeight, (Float64)60);
    // Match Element and Value (IS)
    auto testOK3 = router::conditions::ElementMatch<EVR_IS>::New(dataset, DCM_StageNumber, (Sint32)12);
    
    // Test
    std::cout << "test ok 1: " << (testOK1->eval() ? "OK" : "KO") << std::endl;
    std::cout << "test ok 2: " << (testOK2->eval() ? "OK" : "KO") << std::endl;
    std::cout << "test ok 3: " << (testOK3->eval() ? "OK" : "KO") << std::endl;
    std::cout << "test ko 1: " << (testKO1->eval() ? "KO" : "OK") << std::endl;
    std::cout << "test ko 2: " << (testKO2->eval() ? "KO" : "OK") << std::endl;
    std::cout << "test ko 3: " << (testKO3->eval() ? "KO" : "OK") << std::endl;
    
    return EXIT_SUCCESS;
}
