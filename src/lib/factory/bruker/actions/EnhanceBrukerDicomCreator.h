/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1a579cc1_2225_4838_ad84_f61bf7806b7e
#define _1a579cc1_2225_4838_ad84_f61bf7806b7e

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{
    
class EnhanceBrukerDicomCreator : public CreatorBase
{
public:
    typedef EnhanceBrukerDicomCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~EnhanceBrukerDicomCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "EnhanceBrukerDicom"; }

protected:
    EnhanceBrukerDicomCreator();
    
private:
    EnhanceBrukerDicomCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace factory

} // namespace dicomifier

#endif // _1a579cc1_2225_4838_ad84_f61bf7806b7e
