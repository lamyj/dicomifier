/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ea5295c2_2ec4_48a4_9856_b6933d332878
#define _ea5295c2_2ec4_48a4_9856_b6933d332878

#include "translator/filters/PatientPositionFilter.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The PatientPositionFilterCreator class
 */
class PatientPositionFilterCreator : public TranslationCreatorBase
{
public:
    typedef PatientPositionFilterCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of PatientPositionFilterCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of PatientPositionFilterCreator
    virtual ~PatientPositionFilterCreator();

    /**
     * @brief Create Pointer to class PatientPositionFilter
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new PatientPositionFilter
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return PatientPositionFilter
     */
    static std::string get_class_name() { return "PatientPositionFilter"; }
    
protected:
    /// Create an instance of PatientPositionFilterCreator
    PatientPositionFilterCreator();

private:
    PatientPositionFilterCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorPatientPositionFilterCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer patientpositionfilter;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _ea5295c2_2ec4_48a4_9856_b6933d332878
