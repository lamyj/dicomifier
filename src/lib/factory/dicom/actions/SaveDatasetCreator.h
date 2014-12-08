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

/**
 * @brief The SaveDatasetCreator class: Factory for the class SaveDataset
 */
class SaveDatasetCreator : public CreatorBase
{
public:
    typedef SaveDatasetCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SaveDatasetCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of SaveDatasetCreator
    virtual ~SaveDatasetCreator();
    
    /**
     * @brief Create an object SaveDataset
     * @param value: XML node
     * @return new instancce of SaveDataset
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return SaveDataset
     */
    static std::string get_class_name() { return "SaveDataset"; }

protected:
    /// Create an instance of SaveDatasetCreator
    SaveDatasetCreator();

private:
    SaveDatasetCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace factory

} // namespace dicomifier

#endif // _42212e5f_ed03_4c90_8e18_43f137a7b260
