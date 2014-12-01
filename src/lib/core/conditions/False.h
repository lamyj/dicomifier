/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f86951f5_4869_47a1_bd24_f082f3f1e8f1
#define _f86951f5_4869_47a1_bd24_f082f3f1e8f1

#include "Condition.h"

namespace dicomifier
{

namespace conditions
{

/**
 * @brief Condition that is always false.
 */
class False: public Condition
{
public:
    typedef False Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of False
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of False
    virtual ~False();

    /**
     * @brief Evaluate the condition.
     * @return False
     */
    virtual bool eval() const;
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "False"; }

protected:
    /// Create an instance of False
    False();

private:
    False(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace conditions

} // namespace dicomifier

#endif // _f86951f5_4869_47a1_bd24_f082f3f1e8f1
