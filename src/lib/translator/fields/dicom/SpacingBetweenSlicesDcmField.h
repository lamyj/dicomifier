/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c8687d83_a052_4256_8c61_f7c2805018b3
#define _c8687d83_a052_4256_8c61_f7c2805018b3

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The SpacingBetweenSlicesDcmField class
 */
template<DcmEVR VR>
class SpacingBetweenSlicesDcmField : public SubTag<VR>
{
public:
    typedef SpacingBetweenSlicesDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SpacingBetweenSlicesDcmField
    static Pointer New();
    
    /// Destroy the instance of SpacingBetweenSlicesDcmField
    virtual ~SpacingBetweenSlicesDcmField();
                     
    /**
     * @brief run: Convert Bruker SpacingBetweenSlicesDcmField format into
     *             DICOM SpacingBetweenSlicesDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_SpacingBetweenSlicesDcmField
     */
    virtual ClassType get_class_type() const 
            { return ECT_SpacingBetweenSlicesDcmField; }

protected:
    /// Create an instance of SpacingBetweenSlicesDcmField
    SpacingBetweenSlicesDcmField();

private:

};

} // namespace translator
    
} // namespace dicomifier

#include "SpacingBetweenSlicesDcmField.txx"

#endif //_c8687d83_a052_4256_8c61_f7c2805018b3
