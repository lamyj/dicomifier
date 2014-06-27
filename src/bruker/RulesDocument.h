#ifndef _a516a283_e1b8_4ab0_aa51_7133c6ffb90e
#define _a516a283_e1b8_4ab0_aa51_7133c6ffb90e
/*! \file RulesDocument.h
*/

#include <string>
#include <vector>

#include "BrukerDirectory.h"
#include "RulesAction.h"

namespace router
{

/**
 * \class RulesDocument
 * \brief This class is a XML document reader/writter for 
 *        Bruker to DICOM converting rules
 */
class RulesDocument
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
                   BrukerFieldData const & data, DcmEVR evr,
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

} // namespace router

#endif // _a516a283_e1b8_4ab0_aa51_7133c6ffb90e
