#include <memory>

#include "core/Rule.h"
#include "core/XmlToRules.h"
#include "wrapper.h"

void execute(std::string xmlfile) throw (dicomifier::DicomifierException)
{
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
