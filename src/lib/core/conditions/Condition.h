/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _710cae4e_7211_4717_bf63_cd9181ce16d7
#define _710cae4e_7211_4717_bf63_cd9181ce16d7

#include <memory>

#include "lib/core/Object.h"


namespace dicomifier
{

namespace conditions
{

/**
 * @brief Abstract base class for all conditions.
 */
class Condition : public Object
{
public:
    typedef Condition Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /**
     * @brief Destructor.
     *
     * The destructor must be public, since shared_ptr must be able to call it.
     */
    virtual ~Condition();

    /**
     * @brief Evaluate the condition.
     */
    virtual bool eval() const =0;
    
    static std::string get_class_name() { return "Condition"; }

protected:
    /**
     * @brief Constructor.
     *
     * The default constructor (and other constructors) shall be protected.
     */
    Condition();

private:
    Condition(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace conditions

} // namespace dicomifier

#endif // _710cae4e_7211_4717_bf63_cd9181ce16d7
