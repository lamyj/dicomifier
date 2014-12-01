/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _758ae8d5_2926_460b_9489_1e280b3d05f8
#define _758ae8d5_2926_460b_9489_1e280b3d05f8

#include <vector>

#include "Condition.h"

namespace dicomifier
{
    
namespace conditions
{
    
/**
 * @brief And-combination of several conditions.
 */
class All: public Condition
{
public:
    typedef All Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of All
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * Create pointer to new instance of All
     * @param left: first condition
     * @param right: second condition
     */
    static Pointer New(Condition::ConstPointer left, Condition::ConstPointer right) { return Pointer(new Self(left, right)); }
    
    /// Destroy the instance of All
    virtual ~All();

    /**
     * @brief Evaluate the condition.
     * @return true if all children condition are met, false otherwise
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
    static std::string get_class_name() { return "All"; }
    
protected:
    /// Create an instance of All
    All();
    
    /**
     * Create an instance of All
     * @param left: first condition
     * @param right: second condition
     */
    All(Condition::ConstPointer left, Condition::ConstPointer right);

private:
    /// List of conditions
    std::vector<Condition::ConstPointer> _children;

    All(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace conditions
    
} // namespace dicomifier

#endif // ALL_H
