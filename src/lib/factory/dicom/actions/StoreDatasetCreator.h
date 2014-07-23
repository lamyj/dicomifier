/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _468e8109_5aba_4868_a5ae_07b05d928844
#define _468e8109_5aba_4868_a5ae_07b05d928844

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
class StoreDatasetCreator : public CreatorBase
{
public:
    typedef StoreDatasetCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~StoreDatasetCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "StoreDataset"; }

protected:
    StoreDatasetCreator();

private:
    StoreDatasetCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _468e8109_5aba_4868_a5ae_07b05d928844
