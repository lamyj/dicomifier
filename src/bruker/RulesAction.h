#ifndef RULESACTION_H
#define RULESACTION_H
/*! \file RulesAction.h
*/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "BrukerSystem.h"

enum EActionType {
    AT_Set_Element,
    AT_Empty_Element,
    AT_Delete_Element
};

enum EValueRepresentation {
    VR_AE,
    VR_AS,
    VR_AT,
    VR_CS,
    VR_DA,
    VR_DS,
    VR_DT,
    VR_FL,
    VR_FD,
    VR_IS,
    VR_LO,
    VR_LT,
    VR_OB,
    VR_OD,
    VR_OF,
    VR_OW,
    VR_PN,
    VR_SH,
    VR_SL,
    VR_SQ,
    VR_SS,
    VR_ST,
    VR_TM,
    VR_UI,
    VR_UL,
    VR_UN,
    VR_US,
    VR_UT
};

/**
 * \class RulesAction
 * \brief This class defines Actions for Bruker to DICOM converting rules
 */
class creaBruker_ICUBE_EXPORT RulesAction
{
public:
    /**
     * Constructor
     */
    RulesAction(EActionType actiontype);
    
    /**
     * Destructor
     */
    virtual ~RulesAction();
    
    boost::property_tree::ptree toXMLNode();
    
    std::string GetTypeToString() const;
    
    inline void SetElement(std::string const & element)
        { this->_Element = element; }
        
    inline void SetValue(std::string const & value)
        { this->_Value = value; }
        
    inline void SetVR(EValueRepresentation vr)
        { this->_VR = vr; }
        
    static std::string GetValueRepresentationAsString(EValueRepresentation vr);

protected:

private:
    EActionType _actionType;
    
    std::string _Element;
    
    std::string _Value;

    EValueRepresentation _VR;
};

#endif

