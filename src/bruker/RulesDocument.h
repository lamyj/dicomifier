#ifndef RULESDOCUMENT_H
#define RULESDOCUMENT_H
/*! \file RulesDocument.h
*/

#include <string>
#include <vector>

#include "BrukerDirectory.h"
#include "RulesAction.h"

/**
 * \class RulesDocument
 * \brief This class is a XML document reader/writter for 
 *        Bruker to DICOM converting rules
 */
class creaBruker_ICUBE_EXPORT RulesDocument
{
public:
    /**
     * Constructor
     */
    RulesDocument();
    
    /**
     * Destructor
     */
    virtual ~RulesDocument();
    
    void AddAction(RulesAction* action);
    
    void AddAction(EActionType type, std::string const & elementName,
                   BrukerFieldData const & data, EValueRepresentation vr,
                   bool clean = false);
    
    /**
     * Write XML document
     * @param : output xml file name
     */
    void WriteDocument(std::string const & file);

protected:

private:
    std::vector<RulesAction*> _ActionsList;

};

#endif
