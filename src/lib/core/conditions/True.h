/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _470a2cf4_c361_436f_9f8e_b0c22980b983
#define _470a2cf4_c361_436f_9f8e_b0c22980b983

#include "Condition.h"

namespace dicomifier
{

namespace conditions
{

/**
 * @brief Condition that is always true
 */
class True: public Condition
{
public:
    typedef True Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of True
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of True
    virtual ~True();

    /**
     * @brief Evaluate the condition.
     * @return True
     */
    virtual bool eval() const;
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "True"; }

protected:
    /// Create an instance of True
    True();

private:
    True(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};

} // namespace conditions

} // namespace dicomifier

#endif // _470a2cf4_c361_436f_9f8e_b0c22980b983
