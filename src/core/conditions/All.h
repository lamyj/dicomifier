/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _758ae8d5_2926_460b_9489_1e280b3d05f8
#define _758ae8d5_2926_460b_9489_1e280b3d05f8

#include "Condition.h"

#include <vector>

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
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(Condition::ConstPointer left, Condition::ConstPointer right) { return Pointer(new Self(left, right)); }
    
    /**
     * Destructor
     */
    virtual ~All();

    virtual bool eval() const;
    
    static std::string get_class_name() { return "All"; }
    
protected:
    /**
     * Constructor
     */
    All();
    All(Condition::ConstPointer left, Condition::ConstPointer right);

private:
    std::vector<Condition::ConstPointer> _children;

    All(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace conditions
    
} // namespace dicomifier

#endif // ALL_H
