/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCU.h"

#include <sstream>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/cond.h>
#include <dcmtk/dcmnet/dimse.h>

#include "core/DicomifierException.h"

namespace dicomifier
{

SCU
::SCU()
: _own_ae_title(""), _timeout(30),
  _peer_host_name(""), _peer_port(104), _peer_ae_title(""),
  _user_identity_type(UserIdentityType::None), 
  _user_identity_primary_field(""), _user_identity_secondary_field(""),
  _affected_sop_class(""),
  _network(NULL), _association(NULL)
{
    // Nothing else
}

SCU
::SCU(SCU const & other)
: _own_ae_title(other._own_ae_title), _timeout(other._timeout),
  _peer_host_name(other._peer_host_name), 
  _peer_port(other._peer_port), 
  _peer_ae_title(other._peer_ae_title),
  _user_identity_type(other._user_identity_type), 
  _user_identity_primary_field(other._user_identity_primary_field), 
  _user_identity_secondary_field(other._user_identity_secondary_field),
  _affected_sop_class(other._affected_sop_class),
  _network(NULL), _association(NULL)
{
    if(other.is_associated())
    {
        this->associate();
    }
}

SCU const &
SCU
::operator=(SCU const & other)
{
    if(this != &other)
    {
        bool re_associate = false;
        
        re_associate |= (this->get_own_ae_title() != other.get_own_ae_title());
        
        re_associate |= (this->get_timeout() != other.get_timeout());
        
        re_associate |= (this->get_peer_host_name() != other.get_peer_host_name());
        re_associate |= (this->get_peer_port() != other.get_peer_port());
        re_associate |= (this->get_peer_ae_title() != other.get_peer_ae_title());
        
        re_associate |= (this->get_user_identity_type() != other.get_user_identity_type());
        re_associate |= (this->get_user_identity_primary_field() != other.get_user_identity_primary_field());
        re_associate |= (this->get_user_identity_secondary_field() != other.get_user_identity_secondary_field());
        
        this->set_own_ae_title(other.get_own_ae_title());
        
        this->set_timeout(other.get_timeout());
        
        this->set_peer_host_name(other.get_peer_host_name());
        this->set_peer_port(other.get_peer_port());
        this->set_peer_ae_title(other.get_peer_ae_title());
        
        this->set_user_identity_type(other.get_user_identity_type());
        this->set_user_identity_primary_field(other.get_user_identity_primary_field());
        this->set_user_identity_secondary_field(other.get_user_identity_secondary_field());
        
        if(re_associate)
        {
            if(this->is_associated())
            {
                this->release();
            }
            if(other.is_associated())
            {
                this->associate();
            }
        }
        
        this->set_affected_sop_class(other.get_affected_sop_class());
    }
    
    return *this;
}

SCU
::~SCU()
{
    if(this->is_associated())
    {
        this->release();
    }
}

std::string const &
SCU
::get_own_ae_title() const
{
    return this->_own_ae_title;
}

void
SCU
::set_own_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_own_ae_title = ae_title;
}

unsigned int
SCU
::get_timeout() const
{
    return this->_timeout;
}

void
SCU
::set_timeout(unsigned int timeout)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_timeout = timeout;
}

std::string const &
SCU
::get_peer_host_name() const
{
    return this->_peer_host_name;
}

void
SCU
::set_peer_host_name(std::string const & host_name)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_peer_host_name = host_name;
}

uint16_t
SCU
::get_peer_port() const
{
    return this->_peer_port;
}

void
SCU
::set_peer_port(uint16_t port)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_peer_port = port;
}

std::string const &
SCU
::get_peer_ae_title() const
{
    return this->_peer_ae_title;
}

void
SCU
::set_peer_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_peer_ae_title = ae_title;
}

void
SCU
::add_presentation_context(std::string const & abstract_syntax,
    std::vector<std::string> const & transfer_syntaxes)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_presentation_contexts.push_back(
        std::make_pair(abstract_syntax, transfer_syntaxes));
}

UserIdentityType
SCU
::get_user_identity_type() const
{
    return this->_user_identity_type;
}

void
SCU
::set_user_identity_type(UserIdentityType type)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_user_identity_type = type;
}

std::string const &
SCU
::get_user_identity_primary_field() const
{
    return this->_user_identity_primary_field;
}

void
SCU
::set_user_identity_primary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_user_identity_primary_field = value;
}

std::string const &
SCU
::get_user_identity_secondary_field() const
{
    return this->_user_identity_secondary_field;
}

void
SCU
::set_user_identity_secondary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw DicomifierException("Cannot set member while associated");
    }
    
    this->_user_identity_secondary_field = value;
}

void
SCU
::set_user_identity_to_none()
{
    this->set_user_identity_type(UserIdentityType::None);
    this->set_user_identity_primary_field("");
    this->set_user_identity_secondary_field("");
}

void
SCU
::set_user_identity_to_username(std::string const & username)
{
    this->set_user_identity_type(UserIdentityType::Username);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field("");
}

void
SCU
::set_user_identity_to_username_and_password(std::string const & username, std::string const & password)
{
    this->set_user_identity_type(UserIdentityType::UsernameAndPassword);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field(password);
}

void
SCU
::set_user_identity_to_kerberos(std::string const & ticket)
{
    this->set_user_identity_type(UserIdentityType::Kerberos);
    this->set_user_identity_primary_field(ticket);
    this->set_user_identity_secondary_field("");
}

void
SCU
::set_user_identity_to_saml(std::string const & assertion)
{
    this->set_user_identity_type(UserIdentityType::SAML);
    this->set_user_identity_primary_field(assertion);
    this->set_user_identity_secondary_field("");
}

bool
SCU
::is_associated() const
{
    return (this->_association != NULL);
}

void
SCU
::associate()
{
    if(this->is_associated())
    {
        throw DicomifierException("Already associated");
    }
    
    OFCondition condition;
    
    condition = ASC_initializeNetwork(NET_REQUESTOR, 0, this->_timeout, 
        &this->_network);
    if(!condition.good())
    {
        throw DicomifierException(condition.text());
    }
    
    T_ASC_Parameters * params;
    condition = ASC_createAssociationParameters(&params, ASC_MAXIMUMPDUSIZE);
    if(!condition.good())
    {
        throw DicomifierException(condition.text());
    }
    
    condition = ASC_setAPTitles(params, 
        this->_own_ae_title.c_str(), this->_peer_ae_title.c_str(), NULL);
    if(!condition.good())
    {
        throw DicomifierException(condition.text());
    }
    
    std::string localhost(128, '\0');
    gethostname(&localhost[0], localhost.size()-1);
    
    std::ostringstream peer;
    peer << this->_peer_host_name << ":" << this->_peer_port;
    
    condition = ASC_setPresentationAddresses(params,
        "localhost", peer.str().c_str());
    if(!condition.good())
    {
        throw DicomifierException(condition.text());
    }
    
    unsigned int context_id = 1;
    for(auto const & context: this->_presentation_contexts)
    {
        char const ** transfer_syntaxes = new char const *[context.second.size()];
        for(std::size_t i = 0; i < context.second.size(); ++i)
        {
            transfer_syntaxes[i] = context.second[i].c_str();
        }
        
        condition = ASC_addPresentationContext(params, 
            context_id, context.first.c_str(), 
            transfer_syntaxes, context.second.size());
        if(!condition.good())
        {
            throw DicomifierException(condition.text());
        }
        
        context_id += 2;
    }
    
    if(this->_user_identity_type == UserIdentityType::None)
    {
        // Nothing to do.
    }
    else if(this->_user_identity_type == UserIdentityType::Username)
    {
        condition = ASC_setIdentRQUserOnly(params, 
            this->_user_identity_primary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::UsernameAndPassword)
    {
        condition = ASC_setIdentRQUserPassword(params, 
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_secondary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::Kerberos)
    {
        condition = ASC_setIdentRQKerberos(params, 
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else if(this->_user_identity_type == UserIdentityType::SAML)
    {
        condition = ASC_setIdentRQSaml(params, 
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else
    {
        throw DicomifierException("Unknown identity type");
    }
    
    if(!condition.good())
    {
        throw DicomifierException(condition.text());
    }
    
    condition = ASC_requestAssociation(this->_network, params, &this->_association);
    if(!condition.good())
    {
        OFString empty;
        
        if(condition == DUL_ASSOCIATIONREJECTED)
        {
            T_ASC_RejectParameters rej;
            ASC_getRejectParameters(params, &rej);
            
            throw DicomifierException(ASC_printRejectParameters(empty, &rej).c_str());
        } 
        else 
        {
            throw DicomifierException(DimseCondition::dump(empty, condition).c_str());
        }
    }
}

void
SCU
::release()
{
    if(!this->is_associated())
    {
        throw DicomifierException("Not associated");
    }
    
    ASC_releaseAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
    
    ASC_dropNetwork(&this->_network);
    this->_network = NULL;
}

void
SCU
::abort()
{
    if(!this->is_associated())
    {
        throw DicomifierException("Not associated");
    }
    
    ASC_abortAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
    
    ASC_dropNetwork(&this->_network);
    this->_network = NULL;
}

std::string const &
SCU
::get_affected_sop_class() const
{
    return this->_affected_sop_class;
}
    
void 
SCU
::set_affected_sop_class(std::string const & sop_class)
{
    this->_affected_sop_class = sop_class;
}

void
SCU
::echo() const
{
    if(!this->is_associated())
    {
        throw DicomifierException("Not associated");
    }
    
    DIC_US const message_id = this->_association->nextMsgID++;
    DIC_US status;
    DcmDataset *detail = NULL;
    // FIXME: block mode and timeout
    OFCondition const condition = DIMSE_echoUser(this->_association, 
        message_id, DIMSE_BLOCKING, 30, &status, &detail);
    
    if(!condition.good())
    {
        OFString empty;
        throw DicomifierException(DimseCondition::dump(empty, condition).c_str());
    }
}

} // namespace dicomifier
