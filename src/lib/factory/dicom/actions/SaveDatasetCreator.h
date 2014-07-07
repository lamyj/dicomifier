/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _42212e5f_ed03_4c90_8e18_43f137a7b260
#define _42212e5f_ed03_4c90_8e18_43f137a7b260

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
	
namespace factory
{
	
class SaveDatasetCreator : public CreatorBase
{
public:
    typedef SaveDatasetCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~SaveDatasetCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "SaveDataset"; }

protected:
    SaveDatasetCreator();

private:
    SaveDatasetCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};	
	
} // namespace factory	

} // namespace dicomifier

#endif // _42212e5f_ed03_4c90_8e18_43f137a7b260
