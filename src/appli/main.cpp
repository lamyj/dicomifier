/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <memory>

#include <dcmtk/dcmdata/dctk.h>

#include "core/XmlToRules.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: Argument is missing." << std::endl;
        return EXIT_FAILURE;
    }
    
    std::string const filename = argv[1];
    
    std::vector<dicomifier::Object::Pointer> rules = 
                    dicomifier::XmlToRules::Convert(filename);
    
    std::cout << "rules.size = " << rules.size() << std::endl;
    return EXIT_SUCCESS;
}
