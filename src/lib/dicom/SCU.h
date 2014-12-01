/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ba1518e7_8123_46c9_81c0_65439717e40e
#define _ba1518e7_8123_46c9_81c0_65439717e40e

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/assoc.h>

namespace dicomifier
{

/// User identity types as defined by PS3.8 2013 D.3.3.7
enum class UserIdentityType
{
    None = 0,
    Username = 1,
    UsernameAndPassword = 2,
    Kerberos = 3,
    SAML = 4
};

/**
 * @brief Base class for all SCU.
 * 
 * Objects of this class may not call setters when associated.
 * 
 */
class SCU
{
public:
    
    /// Create a default, non-associated SCU.
    SCU();
    
    /// Copy the other SCU. Associate if other is associated.
    SCU(SCU const & other);
    
    /// Copy the other SCU. Associate if other is associated.
    SCU const & operator=(SCU const & other);
    
    /// Destroy the SCU. Release the association if existing.
    virtual ~SCU();
    
    /// Return the AE title of the caller. Defaults to "".
    std::string const & get_own_ae_title() const;
    /// Set the AE title of the caller.
    void set_own_ae_title(std::string const & ae_title);
    
    /// Return the timeout for network operations, in seconds. Defaults to 30.
    unsigned int get_timeout() const;
    void set_timeout(unsigned int timeout);
    
    /// @name Peer
    /// @{
    
    /// Return the host name of the peer. Defaults to "".
    std::string const & get_peer_host_name() const;
    /// Set the host name of the peer.
    void set_peer_host_name(std::string const & host_name);
    
    /// Return the port of the peer. Defaults to 104.
    uint16_t get_peer_port() const;
    /// Set the port of the peer.
    void set_peer_port(uint16_t port);
    
    /// Return the AE title of the peer. Defaults to "".
    std::string const & get_peer_ae_title() const;
    /// Set the AE title of the peer.
    void set_peer_ae_title(std::string const & ae_title);
    
    /// @}
    
    /// @name Presentation contexts
    /// @{
    
    void add_presentation_context(std::string const & abstract_syntax,
        std::vector<std::string> const & transfer_syntaxes);
    
    /// @}
    
    /// @name User identity
    /// @{
        
    /// Return the user identity type. Defaults to None.
    UserIdentityType get_user_identity_type() const;
    /// Set the user identity type.
    void set_user_identity_type(UserIdentityType type);
    
    /// Return the user identity primary field. Defaults to "".
    std::string const & get_user_identity_primary_field() const;
    /// Set the user identity primary field. 
    void set_user_identity_primary_field(std::string const & value);
    
    /// Return the user identity secondary field. Defaults to "".
    std::string const & get_user_identity_secondary_field() const;
    /// Set the user identity secondary field.
    void set_user_identity_secondary_field(std::string const & value);
    
    /// Do no authenticate user.
    void set_user_identity_to_none();
    
    /// Authenticate user using only a username.
    void set_user_identity_to_username(std::string const & username);
    
    /// Authenticate user using a username and a password.
    void set_user_identity_to_username_and_password(
        std::string const & username, std::string const & password);
        
    /// Authenticate user using a Kerberos ticket.
    void set_user_identity_to_kerberos(std::string const & ticket);
    
    /// Authenticate user using a SAML assertion.
    void set_user_identity_to_saml(std::string const & assertion);
    
    /// @}
    
    /// @name Association
    /// @{
    
    /// Test whether the object is currently associated to its peer.
    bool is_associated() const;
    
    /// Associate with the peer. Throws an exception if already associated.
    void associate();
    /// Gracefully release the association. Throws an exception if not associated.
    void release();
    /// Forcefully release the association. Throws an exception if not associated.
    void abort();
    
    /// @}
    
    /// @name Services
    /// @{
    
    /// Return the affected SOP class. Defaults to "".
    std::string const & get_affected_sop_class() const;
    
    /// Set the affected SOP class
    void set_affected_sop_class(std::string const & sop_class);
    
    /// Perform DICOM ping
    void echo() const;
    
    /// @}

protected:
    std::string _own_ae_title;
    
    int _timeout;
    
    std::string _peer_host_name;
    uint16_t _peer_port;
    std::string _peer_ae_title;
    
    typedef std::pair<std::string, std::vector<std::string> > PresentationContext;
    std::vector<PresentationContext> _presentation_contexts;
    
    UserIdentityType _user_identity_type;
    std::string _user_identity_primary_field;
    std::string _user_identity_secondary_field;
    
    std::string _affected_sop_class;
    
    mutable T_ASC_Network * _network;
    mutable T_ASC_Association * _association;
};

} // namespace dicomifier

#endif // _ba1518e7_8123_46c9_81c0_65439717e40e
