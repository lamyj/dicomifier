/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _01f332b4_9927_4b74_84e5_dd72c753c693
#define _01f332b4_9927_4b74_84e5_dd72c753c693

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The PatientPositionFilter class
 */
template<DcmEVR VR>
class PatientPositionFilter : public SubTag<VR>
{
public:
    typedef PatientPositionFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of PatientPositionFilter
    static Pointer New();
    
    /**
     * @brief New
     * @param tag: VisuSubjectPosition PatientPositionFilter
     * @return
     */
    static Pointer New(Tag::Pointer tag);

    /// Destroy the instance of PatientPositionFilter
    virtual ~PatientPositionFilter();
    
    /**
     * @brief run: Convert Bruker PatientPositionFilter format into
     *             DICOM PatientPositionFilter format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of PatientPositionFilter
    PatientPositionFilter();
    
    /**
     * @brief Create an instance of PatientPositionFilter
     * @param tag: VisuSubjectPosition BrukerField
     */
    PatientPositionFilter(Tag::Pointer tag);

private:
    /// VisuSubjectPosition BrukerField
    Tag::Pointer _tag;

};

} // namespace translator
    
} // namespace dicomifier

#include "PatientPositionFilter.txx"

#endif // _01f332b4_9927_4b74_84e5_dd72c753c693
