/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4cdc3427_f5a6_4bd1_9453_6a278de4f93b
#define _4cdc3427_f5a6_4bd1_9453_6a278de4f93b

#include "translator/SubTag.h"

namespace dicomifier
{

namespace translator
{

template<DcmEVR VR>
class EffectiveEchoTimeDcmField : public SubTag<VR>
{
public:
    typedef EffectiveEchoTimeDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of EffectiveEchoTimeDcmField
    static Pointer New();

    /// Destroy the instance of EffectiveEchoTimeDcmField
    virtual ~EffectiveEchoTimeDcmField();

    /**
     * @brief run: Convert Bruker EffectiveEchoTimeDcmField format into
     *             DICOM EffectiveEchoTimeDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

protected:
    /// Create an instance of EffectiveEchoTimeDcmField
    EffectiveEchoTimeDcmField();

private:

};

} // namespace translator

} // namespace dicomifier

#include "EffectiveEchoTimeDcmField.txx"

#endif // _4cdc3427_f5a6_4bd1_9453_6a278de4f93b
