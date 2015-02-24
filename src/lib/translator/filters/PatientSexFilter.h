/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0a335666_dcb5_4ac1_baf7_a04c8f15d504
#define _0a335666_dcb5_4ac1_baf7_a04c8f15d504

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The PatientSexFilter class
 */
template<DcmEVR VR>
class PatientSexFilter : public SubTag<VR>
{
public:
    typedef PatientSexFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of PatientSexFilter
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of PatientSexFilter
     * @param tag: VisuSubjectSex BrukerField
     * @return new instance of PatientSexFilter
     */
    static Pointer New(Tag::Pointer tag);

    /// Destroy the instance of PatientSexFilter
    virtual ~PatientSexFilter();
    
    /**
     * @brief run: Convert Bruker PatientSexFilter format into
     *             DICOM PatientSexFilter format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of PatientSexFilter
    PatientSexFilter();
    
    /**
     * @brief Create an instance of PatientSexFilter
     * @param tag: VisuSubjectSex BrukerField
     */
    PatientSexFilter(Tag::Pointer tag);

private:
    /// VisuSubjectSex BrukerField
    Tag::Pointer _tag;

};

} // namespace translator
    
} // namespace dicomifier

#include "PatientSexFilter.txx"

#endif // _0a335666_dcb5_4ac1_baf7_a04c8f15d504
