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
    
/**
 * @brief The EnhanceBrukerDicomCreator class: Factory for the class EnhanceBrukerDicom
 */
class EnhanceBrukerDicomCreator : public CreatorBase
{
public:
    typedef EnhanceBrukerDicomCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of EnhanceBrukerDicomCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of EnhanceBrukerDicomCreator
    virtual ~EnhanceBrukerDicomCreator();
    
    /**
     * @brief Create: Create an Action EnhanceBrukerDicom
     * @param value: XML node
     * @return new instance of EnhanceBrukerDicom
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return EnhanceBrukerDicom
     */
    static std::string get_class_name() { return "EnhanceBrukerDicom"; }

protected:
    /// Create an instance of EnhanceBrukerDicomCreator
    EnhanceBrukerDicomCreator();
    
private:
    EnhanceBrukerDicomCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace factory

} // namespace dicomifier

#endif // _1a579cc1_2225_4838_ad84_f61bf7806b7e
