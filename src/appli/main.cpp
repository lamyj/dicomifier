/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <memory>

#include "core/Rule.h"
#include "core/XmlToRules.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Argument is missing." << std::endl;
        return EXIT_FAILURE;
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
            std::cout << "Error: Created object is not a Rule." << std::endl;
        }
    }
            
    return EXIT_SUCCESS;
}
