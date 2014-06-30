/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

/**
 * Transform private Bruker tree structure
 * into the equivalent, with DICOM files. 
 * 
 */
#include <cstdlib>
#include <exception>

#include "lib/bruker/Bruker2Dicom.h"

// ===================================================================================================

int main(int argc, char *argv[])
{    
    dicomifier::Bruker2Dicom converter;
    
    try
    {
        if (converter.Execute(argv[1], argv[2]))
        {
            std::cout << "Done" << std::endl;
        }
        else
        {
            std::cout << "Error" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}


