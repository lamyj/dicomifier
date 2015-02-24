/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2ff027d3_18a0_45d6_88db_9c57775cddda
#define _2ff027d3_18a0_45d6_88db_9c57775cddda

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The DimensionIndexValuesDcmField class
 */
template<DcmEVR VR>
class DimensionIndexValuesDcmField : public SubTag<VR>
{
public:
    typedef DimensionIndexValuesDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DimensionIndexValuesDcmField
    static Pointer New();
    
    /// Destroy the instance of DimensionIndexValuesDcmField
    virtual ~DimensionIndexValuesDcmField();
                     
    /**
     * @brief run: Convert Bruker DimensionIndexValuesDcmField format into
     *             DICOM DimensionIndexValuesDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

protected:
    /// Create an instance of DimensionIndexValuesDcmField
    DimensionIndexValuesDcmField();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#include "DimensionIndexValuesDcmField.txx"

#endif // _2ff027d3_18a0_45d6_88db_9c57775cddda
