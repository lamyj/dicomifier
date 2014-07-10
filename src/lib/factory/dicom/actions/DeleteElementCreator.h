/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _37a5805a_01e5_4260_b98f_ec43f0828738
#define _37a5805a_01e5_4260_b98f_ec43f0828738

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class DeleteElementCreator : public CreatorBase
{
public:
    typedef DeleteElementCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~DeleteElementCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "DeleteElement"; }

protected:
    DeleteElementCreator();

private:
    DeleteElementCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _37a5805a_01e5_4260_b98f_ec43f0828738
