/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2d8d2ead_aa9a_49c9_818d_86a1082b0e80
#define _2d8d2ead_aa9a_49c9_818d_86a1082b0e80

#include "factory/core/CreatorBase.h"

namespace dicomifier
{

namespace factory
{
    
class PrintDatasetCreator : public CreatorBase
{
public:
    typedef PrintDatasetCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~PrintDatasetCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "PrintDataset"; }
    
protected:
    PrintDatasetCreator();

private:
    PrintDatasetCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace factory

} // namespace dicomifier

#endif // _2d8d2ead_aa9a_49c9_818d_86a1082b0e80
