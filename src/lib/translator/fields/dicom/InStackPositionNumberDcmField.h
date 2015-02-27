/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6df1176c_6677_49ae_8ac1_5095e7aadab3
#define _6df1176c_6677_49ae_8ac1_5095e7aadab3

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The InStackPositionNumberDcmField class
 */
template<DcmEVR VR>
class InStackPositionNumberDcmField : public SubTag<VR>
{
public:
    typedef InStackPositionNumberDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InStackPositionNumberDcmField
    static Pointer New();
    
    /// Destroy the instance of InStackPositionNumberDcmField
    virtual ~InStackPositionNumberDcmField();
                     
    /**
     * @brief run: Convert Bruker InStackPositionNumberDcmField format into
     *             DICOM InStackPositionNumberDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

protected:
    /// Create an instance of InStackPositionNumberDcmField
    InStackPositionNumberDcmField();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#include "InStackPositionNumberDcmField.txx"

#endif // _6df1176c_6677_49ae_8ac1_5095e7aadab3
