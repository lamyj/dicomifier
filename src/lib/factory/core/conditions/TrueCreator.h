/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8690cd8b_8e24_44f1_a3b2_b1715c563947
#define _8690cd8b_8e24_44f1_a3b2_b1715c563947

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{

/**
 * @brief The TrueCreator class: Factory for the class True
 */
class TrueCreator : public CreatorBase
{
public:
    typedef TrueCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of TrueCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of TrueCreator
    virtual ~TrueCreator();
    
    /**
     * @brief Create an object True
     * @param value: XML node
     * @return new instancce of True
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return True
     */
    static std::string get_class_name() { return "True"; }

protected:
    /// Create an instance of TrueCreator
    TrueCreator();

private:
    TrueCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _8690cd8b_8e24_44f1_a3b2_b1715c563947
