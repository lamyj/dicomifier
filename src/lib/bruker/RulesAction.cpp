/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "RulesAction.h"

namespace dicomifier
{

RulesAction::RulesAction(EActionType actiontype):
    _actionType(actiontype),
    _Element(""),
    _Value(""),
    _VR(EVR_UN)
{
}

RulesAction::~RulesAction()
{
}

boost::property_tree::ptree RulesAction::toXMLNode()
{
    boost::property_tree::ptree node;
    
    node.put("<xmlattr>.tag", this->_Element);
    node.put("<xmlattr>.value", this->_Value);
    DcmVR vr(this->_VR);
    node.put("<xmlattr>.VR", std::string(vr.getVRName()));
    
    return node;
}

std::string RulesAction::GetTypeToString() const
{
    switch (this->_actionType)
    {
        case AT_Set_Element:
            return "SetElement";
            
        case AT_Empty_Element:
            return "EmptyElement";
        
        case AT_Delete_Element:
            return "DeleteElement";
    
        default:
            break;
    }
    return "Unknown";
}

} // namespace dicomifier