/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <memory>

#include "core/Rule.h"
#include "core/XmlToRules.h"
#include "dicom/Dictionaries.h"
#include "wrapper.h"

void execute(std::string xmlfile, std::string privatedictionary) throw (dicomifier::DicomifierException)
{
    if (privatedictionary != "")
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary(privatedictionary);
    }
    
    std::vector<dicomifier::Object::Pointer> rules = 
                    dicomifier::XmlToRules::Convert(xmlfile);
    
    for (auto it = rules.begin(); it != rules.end(); it++)
    {
        dicomifier::Rule::Pointer rule = 
                std::dynamic_pointer_cast<dicomifier::Rule>(*it);
           
        if (rule != NULL)
        {
            rule->Execute();
        }
    }
}
