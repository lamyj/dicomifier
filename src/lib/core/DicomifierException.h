/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7e73d887_9f2a_46ba_a4bd_049bb2aebd97
#define _7e73d887_9f2a_46ba_a4bd_049bb2aebd97

#include <exception>
#include <string>

namespace dicomifier
{
    
/**
 * \class DicomifierException
 * \brief Generic exception
 */
class DicomifierException: public std::exception
{
public:
    /**
     * Create an instance of DicomifierException
     * @param message: details about this exception
     */
    DicomifierException(const std::string& message):
        m_message(message) {}

    /// Destroy the exception
    virtual ~DicomifierException() throw() {}
    
    /**
     * Return details about this exception
     * @return Exception details
     */
    virtual const char* what() const throw() {
        return m_message.c_str();
    }
    
protected:
    /// Exception details
    std::string m_message;

private:

};

} // namespace dicomifier

#endif // _7e73d887_9f2a_46ba_a4bd_049bb2aebd97
