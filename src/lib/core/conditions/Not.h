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

    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(Condition::ConstPointer condition) { return Pointer(new Self(condition)); }
    
    /**
     * @brief Destructor
     */
    virtual ~Not();
    
    virtual bool eval() const;
    
    static std::string get_class_name() { return "Not"; }
    
protected:
    /**
     * @brief Constructor
     */
    Not();
    Not(Condition::ConstPointer condition);

private:
    Condition::ConstPointer _condition;

    Not(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions
    
} // namespace dicomifier

#endif // NOT_H
