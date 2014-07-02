/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b07764f2_55d7_4b6a_970e_ee741b69f1b0
#define _b07764f2_55d7_4b6a_970e_ee741b69f1b0

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{
    
class ElementMatchCreator : public CreatorBase
{
public:
    typedef ElementMatchCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~ElementMatchCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) const;

    static std::string get_class_name() { return "ElementMatch"; }
    
    template<DcmEVR VR>
    Object::Pointer Create(DcmDataset* dataset, DcmTag const & tag, std::string const & value) const;

protected:
    ElementMatchCreator();

private:
    ElementMatchCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _b07764f2_55d7_4b6a_970e_ee741b69f1b0
