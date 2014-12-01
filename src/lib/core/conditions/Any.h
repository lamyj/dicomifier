/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _805413fc_20b1_422c_9b88_3395c07a47ca
#define _805413fc_20b1_422c_9b88_3395c07a47ca

#include <vector>

#include "Condition.h"

namespace dicomifier
{

namespace conditions
{

/**
 * @brief OR-combination of conditions.
 */
class Any: public Condition
{
public:
    typedef Any Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of Any
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * Create pointer to new instance of Any
     * @param left: first condition
     * @param right: second condition
     */
    static Pointer New(Condition::ConstPointer left, Condition::ConstPointer right) { return Pointer(new Self(left, right)); }
    
    /// Destroy the instance of Any
    virtual ~Any();

    /**
     * @brief Evaluate the condition.
     * @return true if one of children condition is met, false otherwise
     */
    virtual bool eval() const;
    
    /**
     * Add a condition
     * @param child: new condition
     */
    void add_child(Condition::ConstPointer child);
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "Any"; }

protected:
    /// Create an instance of Any
    Any();
    
    /**
     * Create an instance of Any
     * @param left: first condition
     * @param right: second condition
     */
    Any(Condition::ConstPointer left, Condition::ConstPointer right);

private:
    /// List of conditions
    std::vector<Condition::ConstPointer> _children;

    Any(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace conditions

} // namespace dicomifier

#endif // _805413fc_20b1_422c_9b88_3395c07a47ca
