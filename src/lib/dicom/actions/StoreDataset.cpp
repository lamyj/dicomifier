/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "dicom/StoreSCU.h"
#include "StoreDataset.h"

namespace dicomifier
{
    
namespace actions
{

/****************************** Constructor *****************************/

StoreDataset
::StoreDataset()
    : Action(), _dataset(NULL), _address(""), _port(0),
      _AEremote(""), _AElocal(""),
      _user_identity_type(UserIdentityType::None),
      _user_identity_primary_field(""), _user_identity_secondary_field("")
{
    // Nothing to do
}

StoreDataset
::StoreDataset(DcmDataset* dataset,
               std::string const & address, Uint16 const & port,
               std::string const & aeremote, std::string const & aelocal,
               UserIdentityType const & user_identity_type,
               std::string const & user_identity_primary_field,
               std::string const & user_identity_secondary_field)
    : Action(), _dataset(dataset), _address(address), _port(port),
      _AEremote(aeremote), _AElocal(aelocal),
      _user_identity_type(user_identity_type),
      _user_identity_primary_field(user_identity_primary_field),
      _user_identity_secondary_field(user_identity_secondary_field)
{
    // Nothing to do
}

/****************************** Destructor ******************************/

StoreDataset
::~StoreDataset()
{
    // Nothing to do
}

/****************************** Accessors *******************************/

UserIdentityType
StoreDataset
::get_user_identity_type() const
{
    return this->_user_identity_type;
}

void
StoreDataset
::set_user_identity_type(UserIdentityType type)
{
    this->_user_identity_type = type;
}

std::string const &
StoreDataset
::get_user_identity_primary_field() const
{
    return this->_user_identity_primary_field;
}

void
StoreDataset
::set_user_identity_primary_field(std::string const & value)
{
    this->_user_identity_primary_field = value;
}

std::string const &
StoreDataset
::get_user_identity_secondary_field() const
{
    return this->_user_identity_secondary_field;
}

void
StoreDataset
::set_user_identity_secondary_field(std::string const & value)
{
    this->_user_identity_secondary_field = value;
}

/****************************** Other Functions *************************/

void
StoreDataset
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Dataset is NULL");
    }
    
    // Get abstract syntax from dataset
    std::string sop_class_uid;
    {
        OFString value;
        this->_dataset->findAndGetOFStringArray(DCM_SOPClassUID, value);
        sop_class_uid = value.c_str();
    }
    
    dicomifier::StoreSCU myscu;
    
    // Set AE title
    myscu.set_own_ae_title(this->_AElocal.c_str());
    
    myscu.set_peer_host_name(this->_address.c_str());
    myscu.set_peer_port(this->_port);
    myscu.set_peer_ae_title(this->_AEremote.c_str());
    
    // Set identity
    myscu.set_user_identity_type(this->_user_identity_type);
    myscu.set_user_identity_primary_field(this->_user_identity_primary_field);
    myscu.set_user_identity_secondary_field(this->_user_identity_secondary_field);
    
    // Set transfer syntax
    myscu.add_presentation_context(sop_class_uid.c_str(),
        { UID_LittleEndianImplicitTransferSyntax });
    myscu.set_affected_sop_class(sop_class_uid);
    
    myscu.associate();
    
    // Do Storage
    myscu.store(this->_dataset);
    
    // Release association
    myscu.release();
}

} // namespace actions
    
} // namespace dicomifier
