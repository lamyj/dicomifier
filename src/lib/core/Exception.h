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

/// @brief Base class for dicomifier exceptions.
class Exception: public std::exception
{
public:
    /// @brief Message string constructor.
    Exception(std::string const & message);

    /// @brief Destructor.
    virtual ~Exception() noexcept;

    /// @brief Return the reason for the exception.
    virtual const char* what() const noexcept;

protected:
    /// @brief Message of the exception.
    std::string _message;
};

}

#endif // _7e73d887_9f2a_46ba_a4bd_049bb2aebd97
