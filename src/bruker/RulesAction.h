/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e4059feb_bb51_4bc4_8b3d_0096f4908ee8
#define _e4059feb_bb51_4bc4_8b3d_0096f4908ee8
/*! \file RulesAction.h
*/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

namespace dicomifier
{

enum EActionType {
    AT_Set_Element,
    AT_Empty_Element,
    AT_Delete_Element
};

/**
 * \class RulesAction
 * \brief This class defines Actions for Bruker to DICOM converting rules
 */
class RulesAction
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
        
    inline void SetVR(DcmEVR vr)
        { this->_VR = vr; }

protected:

private:
    EActionType _actionType;
    
    std::string _Element;
    
    std::string _Value;

    DcmEVR _VR;
};

} // namespace dicomifier

#endif // _e4059feb_bb51_4bc4_8b3d_0096f4908ee8

