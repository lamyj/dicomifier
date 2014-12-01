/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7cbea3af_b521_4280_ae80_aff1fbcd8fca
#define _7cbea3af_b521_4280_ae80_aff1fbcd8fca

#include <dcmtk/config/osconfig.h>  /* make sure OS specific configuration is included first */
#include <dcmtk/dcmdata/dctk.h>     /* Covers most common dcmdata classes */

#include "core/actions/Action.h"
#include "dicom/SCU.h"

namespace dicomifier
{
    
namespace actions
{
    
class StoreDataset : public Action
{
public:
    typedef StoreDataset Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(DcmDataset* dataset, 
        std::string const & address, Uint16 const & port, 
        std::string const & aeremote, std::string const & aelocal, 
        UserIdentityType const & user_identity_type=UserIdentityType::None,
        std::string const & user_identity_primary_field="",
        std::string const & user_identity_secondary_field="") 
        { 
            return Pointer(new Self(
                dataset, address, port, aeremote, aelocal, 
                user_identity_type, 
                user_identity_primary_field, user_identity_secondary_field)); 
        }
    
    virtual ~StoreDataset();

    DcmDataset * get_dataset() const { return this->_dataset; }
    void set_dataset(DcmDataset * dataset) { this->_dataset = dataset; }
    
    std::string get_address() const { return this->_address; }
    void set_address(std::string const & address) { this->_address = address; }
    
    Uint16 get_port() const { return this->_port; }
    void set_port(Uint16 const & port) { this->_port = port; }
    
    std::string get_AEremote() const { return this->_AEremote; }
    void set_AEremote(std::string const & aeremote) { this->_AEremote = aeremote; }
    
    std::string get_AElocal() const { return this->_AElocal; }
    void set_AElocal(std::string const & aelocal) { this->_AElocal = aelocal; }
    
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

    virtual void run() const;
    
    static std::string get_class_name() { return "StoreDataset"; }
    
protected:
    StoreDataset();
    StoreDataset(DcmDataset* dataset, 
        std::string const & address, Uint16 const & port, 
        std::string const & aeremote, std::string const & aelocal, 
        UserIdentityType const & user_identity_type=UserIdentityType::None,
        std::string const & user_identity_primary_field="",
        std::string const & user_identity_secondary_field="");

private:
    DcmDataset* _dataset;
    std::string _address;
    Uint16 _port;
    std::string _AEremote;
    std::string _AElocal;
    UserIdentityType _user_identity_type;
    std::string _user_identity_primary_field;
    std::string _user_identity_secondary_field;

    StoreDataset(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace actions
    
} // namespace dicomifier

#endif // _7cbea3af_b521_4280_ae80_aff1fbcd8fca
