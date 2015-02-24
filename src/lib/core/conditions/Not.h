/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1e3d4e5a_5d40_4459_9b06_062c1f7115be
#define _1e3d4e5a_5d40_4459_9b06_062c1f7115be

#include "Condition.h"

namespace dicomifier
{
    
namespace conditions
{
    
/**
 * @brief Inverse of a condition.
 */
class Not: public Condition
{
public:
    typedef Not Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of Not
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * Create pointer to new instance of Not
     * @param condition: condition to inverse
     */
    static Pointer New(Condition::ConstPointer condition) { return Pointer(new Self(condition)); }
    
    /// Destroy the instance of Not
    virtual ~Not();
    
    /**
     * @brief Evaluate the condition.
     * @return False if child condition is met, true otherwise
     */
    virtual bool eval() const;
    
    /**
     * Get the tested condition
     * @return condition to inverse
     */
    inline Condition::ConstPointer get_condition() const
        { return this->_condition; }
        
    /**
     * Set the tested condition
     * @param condition: new condition to inverse
     */
    inline void set_condition(Condition::ConstPointer condition)
        { this->_condition = condition; }
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "Not"; }
    
protected:
    /// Create an instance of Not
    Not();
    
    /**
     * Create an instance of Not
     * @param condition: condition to inverse
     */
    Not(Condition::ConstPointer condition);

private:
    /// Condition to inverse
    Condition::ConstPointer _condition;

    Not(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions
    
} // namespace dicomifier

#endif // NOT_H
