/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <memory>

#include "core/Logger.h"
#include "core/Rule.h"
#include "core/XmlToRules.h"
#include "dicom/Dictionaries.h"

int main(int argc, char *argv[])
{
    char* mode = getenv("DICOMIFIER_LOGGER");
    std::string logmode = mode != NULL ? std::string(mode): "ERROR";
    dicomifier::InitializeLogger(logmode);

    if (argc < 2)
    {
        dicomifier::loggerError() << "Argument is missing.";
        return EXIT_FAILURE;
    }
    
    if (argc > 2)
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary(argv[2]);
    }
    
    std::string const filename = argv[1];
    
    std::vector<dicomifier::Object::Pointer> rules = 
                    dicomifier::XmlToRules::Convert(filename);
    
    for (auto it = rules.begin(); it != rules.end(); it++)
    {
        dicomifier::Rule::Pointer rule = 
                std::dynamic_pointer_cast<dicomifier::Rule>(*it);
           
        if (rule != NULL)
        {
            rule->Execute();
        }
        else
        {
            dicomifier::loggerError() << "Created object is not a Rule.";
        }
    }
            
    return EXIT_SUCCESS;
}
