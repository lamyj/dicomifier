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
    
class RuleCreator : public CreatorBase
{
public:
    typedef RuleCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~RuleCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) const;

    static std::string get_class_name() { return "Rule"; }
    
protected:
    RuleCreator();

private:
    RuleCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _2055a3c7_a0a9_4536_99d2_0cc3ccaa3551
