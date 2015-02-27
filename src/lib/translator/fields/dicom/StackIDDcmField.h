/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8133a2ff_a47a_4d81_a631_f41b8161d901
#define _8133a2ff_a47a_4d81_a631_f41b8161d901

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The StackIDDcmField class
 */
template<DcmEVR VR>
class StackIDDcmField : public SubTag<VR>
{
public:
    typedef StackIDDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of StackIDDcmField
    static Pointer New();
    
    /// Destroy the instance of StackIDDcmField
    virtual ~StackIDDcmField();
                     
    /**
     * @brief run: Convert Bruker StackIDDcmField format into
     *             DICOM StackIDDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

protected:
    /// Create an instance of StackIDDcmField
    StackIDDcmField();

private:

};

} // namespace translator
    
} // namespace dicomifier

#include "StackIDDcmField.txx"

#endif // _8133a2ff_a47a_4d81_a631_f41b8161d901
