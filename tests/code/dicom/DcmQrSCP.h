/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f515ed49_8c2b_4fc1_b7db_fdc3ec747861
#define _f515ed49_8c2b_4fc1_b7db_fdc3ec747861

#include <stdint.h>
#include <stdlib.h>
#include <string>

#include <boost/lexical_cast.hpp>

/**
 * Test fixture getting the environment variables required to connect to a DICOM
 * query/retrieve SCP.
 */
class DcmQrSCP
{
public:
    
    std::string const data_directory;
    std::string const calling_aet;
    std::string const peer_host;
    uint16_t const peer_port;
    std::string const peer_aet;
    
    DcmQrSCP()
    : data_directory(this->_get_environment_variable("DICOMIFIER_TEST_DATA")),
      calling_aet(this->_get_environment_variable("DICOMIFIER_CALLING_AET")),
      peer_host(this->_get_environment_variable("DICOMIFIER_PEER_HOST")),
      peer_port(this->_get_environment_variable<uint16_t>("DICOMIFIER_PEER_PORT")),
      peer_aet(this->_get_environment_variable("DICOMIFIER_PEER_AET"))
    {
        // Nothing else
    }
    
    ~DcmQrSCP()
    {
        // Nothing to do.
    }
    
private:
    
    std::string _get_environment_variable(std::string const & name) const
    {
        char* value = getenv(name.c_str());
        if(value == NULL)
        {
            BOOST_FAIL(name + " is not defined");
        }
        return value;
    }
    
    template<typename T>
    T _get_environment_variable(std::string const & name) const
    {
        return boost::lexical_cast<T>(this->_get_environment_variable(name));
    }
    
    
};

#endif // _f515ed49_8c2b_4fc1_b7db_fdc3ec747861
