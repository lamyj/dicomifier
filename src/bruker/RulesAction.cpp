
#include "RulesAction.h"

RulesAction::RulesAction(EActionType actiontype):
    _actionType(actiontype),
    _Element(""),
    _Value(""),
    _VR(VR_UN)
{
}

RulesAction::~RulesAction()
{
}

boost::property_tree::ptree RulesAction::toXMLNode()
{
    boost::property_tree::ptree node;
    
    node.put("<xmlattr>.element", this->_Element);
    node.put("<xmlattr>.value", this->_Value);
    node.put("<xmlattr>.VR", RulesAction::GetValueRepresentationAsString(this->_VR));
    
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

std::string RulesAction::GetValueRepresentationAsString(EValueRepresentation vr)
{
    switch (vr)
    {
        case VR_AE:
            return "AE";
            
        case VR_AS:
            return "AS";
            
        case VR_AT:
            return "AT";
            
        case VR_CS:
            return "CS";
            
        case VR_DA:
            return "DA";
            
        case VR_DS:
            return "DS";
            
        case VR_DT:
            return "DT";
            
        case VR_FL:
            return "FL";
            
        case VR_FD:
            return "FD";
            
        case VR_IS:
            return "IS";
            
        case VR_LO:
            return "LO";
            
        case VR_LT:
            return "LT";
            
        case VR_OB:
            return "OB";
            
        case VR_OD:
            return "OD";
            
        case VR_OF:
            return "OF";
            
        case VR_OW:
            return "OW";
            
        case VR_PN:
            return "PN";
            
        case VR_SH:
            return "SH";
            
        case VR_SL:
            return "SL";
            
        case VR_SQ:
            return "SQ";
            
        case VR_SS:
            return "SS";
            
        case VR_ST:
            return "ST";
            
        case VR_TM:
            return "TM";
            
        case VR_UI:
            return "UI";
            
        case VR_UL:
            return "UL";
            
        case VR_US:
            return "US";
            
        case VR_UT:
            return "UT";
            
    }
    
    return "UN";
}
