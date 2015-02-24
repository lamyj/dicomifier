/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2055a3c7_a0a9_4536_99d2_0cc3ccaa3551
#define _2055a3c7_a0a9_4536_99d2_0cc3ccaa3551

#include "CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
/**
 * @brief The RuleCreator class: Factory for the class Rule
 */
class RuleCreator : public CreatorBase
{
public:
    typedef RuleCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of RuleCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of RuleCreator
    virtual ~RuleCreator();
    
    /**
     * @brief Create an object Rule
     * @param value: XML node
     * @return new instance of Rule
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return Rule
     */
    static std::string get_class_name() { return "Rule"; }
    
protected:
    /// Create an instance of RuleCreator
    RuleCreator();

private:
    /**
     * @brief CreateAnyObject: Create object type boost::any with inputs and outputs
     * @param type: Object type
     * @param name: Object name
     * @param value: Object value
     * @return Object as boost::any
     */
	boost::any CreateAnyObject(std::string const & type, 
							   std::string const & name, 
							   std::string const & value);

    RuleCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _2055a3c7_a0a9_4536_99d2_0cc3ccaa3551
