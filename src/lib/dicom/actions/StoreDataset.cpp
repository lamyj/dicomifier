/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <dcmtk/dcmnet/scu.h>

#include "core/DicomifierException.h"
#include "StoreDataset.h"

namespace dicomifier
{
    
namespace actions
{
    
StoreDataset::StoreDataset():
    _dataset(NULL),
    _address(""),
    _port(0),
    _AEremote(""),
    _AElocal("")
{
    // Nothing to do
}

StoreDataset::StoreDataset(DcmDataset* dataset, std::string const & address,
                           Uint16 const & port, std::string const & aeremote,
                           std::string const & aelocal):
    _dataset(dataset),
    _address(address),
    _port(port),
    _AEremote(aeremote),
    _AElocal(aelocal)
{
    // Nothing to do
}

StoreDataset::~StoreDataset()
{
    // Nothing to do
}
    
void
StoreDataset
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Dataset is NULL");
    }
    
    // Get abstract syntax from dataset
    OFString abstractSyntax;
    OFCondition result = this->_dataset->findAndGetOFStringArray(DCM_SOPClassUID, abstractSyntax, OFTrue);
    if (result.bad())
    {
        throw DicomifierException("Unable to retrieve Abstract Syntax");
    }
    
    DcmSCU myscu;
    
    // Set AE title
    myscu.setAETitle(this->_AElocal.c_str());
    myscu.setPeerHostName(this->_address.c_str());
    myscu.setPeerPort(this->_port);
    myscu.setPeerAETitle(this->_AEremote.c_str());
    
    // Set transfert syntax
    OFList<OFString> ts;
    ts.push_back(UID_LittleEndianExplicitTransferSyntax);
    ts.push_back(UID_LittleEndianImplicitTransferSyntax);
    ts.push_back(UID_BigEndianExplicitTransferSyntax);
    
    myscu.addPresentationContext(abstractSyntax, ts);
    
    // Initialize Network
    result = myscu.initNetwork();
    if (result.bad())
    {
        throw DicomifierException("Unable to Initialize network");
    }
    
    // Negotiate association
    result = myscu.negotiateAssociation();
    if (result.bad())
    {
        throw DicomifierException("Unable to Negotiate association");
    }
    
    // Find presentation contexts
    T_ASC_PresentationContextID pcid = myscu.findPresentationContextID(abstractSyntax, "");
    if (pcid == 0)
    {
        throw DicomifierException("No adequate Presentation Contexts");
    }
    
    // Do Storage
    Uint16 rspstatus;
    DcmDataset* rspcommandset;
    DcmDataset* rspstatusdetail;
    result = myscu.sendSTORERequest(pcid, "", this->_dataset, rspcommandset, rspstatusdetail, rspstatus);
    if (result.bad() || rspstatus != 0)
    {
        throw DicomifierException("Could not process C-Store");
    }
    
    // Release association
    myscu.closeAssociation(DCMSCU_RELEASE_ASSOCIATION);
}

} // namespace actions
    
} // namespace dicomifier
