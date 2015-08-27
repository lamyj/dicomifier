/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7cbea3af_b521_4280_ae80_aff1fbcd8fca
#define _7cbea3af_b521_4280_ae80_aff1fbcd8fca

#include <memory>

#include <dcmtk/config/osconfig.h>  /* make sure OS specific configuration is included first */
#include <dcmtk/dcmdata/dctk.h>     /* Covers most common dcmdata classes */

#include "dicom/SCU.h"

namespace dicomifier
{
    
/**
 * @brief The StoreDataset class: Call specific PACS with Store Action
 */
class StoreDataset
{
public:
    typedef StoreDataset Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of StoreDataset
    static Pointer New() { return Pointer(new Self()); }

    /**
     * @brief Create pointer to new instance of StoreDataset
     * @param dataset: Dataset to store
     * @param address: IP of PACS
     * @param port: Port of PACS
     * @param aeremote: Called Name
     * @param aelocal: Calling Name
     * @param user_identity_type: Identity type
     * @param user_identity_primary_field: Identity primary field
     * @param user_identity_secondary_field: Identity secondary field
     * @return pointer to new instance of StoreDataset
     */
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
    
    /// Destroy the instance of StoreDataset
    virtual ~StoreDataset();

    /**
     * @brief get_dataset: getter for attribut Dataset
     * @return dataset
     */
    DcmDataset * get_dataset() const { return this->_dataset; }

    /**
     * @brief set_dataset: setter for attribut Dataset
     * @param dataset: new value
     */
    void set_dataset(DcmDataset * dataset) { this->_dataset = dataset; }
    
    /**
     * @brief get_address: getter for attribut address
     * @return address
     */
    std::string get_address() const { return this->_address; }

    /**
     * @brief set_address: setter for attribut address
     * @param address: new value
     */
    void set_address(std::string const & address) { this->_address = address; }
    
    /**
     * @brief get_port: getter for attribut port
     * @return port
     */
    Uint16 get_port() const { return this->_port; }

    /**
     * @brief set_port: setter for attribut port
     * @param port: new value
     */
    void set_port(Uint16 const & port) { this->_port = port; }
    
    /**
     * @brief get_AEremote: getter for attribut AERemote
     * @return AERemote
     */
    std::string get_AEremote() const { return this->_AEremote; }

    /**
     * @brief set_AEremote: setter for attribut AERemote
     * @param aeremote: new value
     */
    void set_AEremote(std::string const & aeremote) { this->_AEremote = aeremote; }
    
    /**
     * @brief get_AElocal: getter for attribut AELocal
     * @return AELocal
     */
    std::string get_AElocal() const { return this->_AElocal; }

    /**
     * @brief set_AElocal: setter for attribut AELocal
     * @param aelocal: new value
     */
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

    /**
     * @brief run: Execute the action Store
     */
    void run() const;
    
protected:
    /// Create an instance of StoreDataset
    StoreDataset();

    /**
     * @brief Create an instance of StoreDataset
     * @param dataset: Dataset to store
     * @param address: IP of PACS
     * @param port: Port of PACS
     * @param aeremote: Called Name
     * @param aelocal: Calling Name
     * @param user_identity_type: Identity type
     * @param user_identity_primary_field: Identity primary field
     * @param user_identity_secondary_field: Identity secondary field
     */
    StoreDataset(DcmDataset* dataset, 
        std::string const & address, Uint16 const & port, 
        std::string const & aeremote, std::string const & aelocal, 
        UserIdentityType const & user_identity_type=UserIdentityType::None,
        std::string const & user_identity_primary_field="",
        std::string const & user_identity_secondary_field="");

private:
    /// Dataset to store
    DcmDataset* _dataset;

    /// PACS Address
    std::string _address;

    /// PACS Port
    Uint16 _port;

    /// PACS Name
    std::string _AEremote;

    /// Calling Name
    std::string _AElocal;

    /// Identity type
    UserIdentityType _user_identity_type;

    /// Identity primary field
    std::string _user_identity_primary_field;

    /// Identity secondary field
    std::string _user_identity_secondary_field;

    StoreDataset(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace dicomifier

#endif // _7cbea3af_b521_4280_ae80_aff1fbcd8fca
