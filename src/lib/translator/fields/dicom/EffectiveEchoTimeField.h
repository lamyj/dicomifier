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
class EffectiveEchoTimeField : public SubTag<VR>
{
public:
    typedef EffectiveEchoTimeField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of EffectiveEchoTimeField
    static Pointer New();

    /// Destroy the instance of EffectiveEchoTimeField
    virtual ~EffectiveEchoTimeField();

    /**
     * @brief run: Convert Bruker EffectiveEchoTimeField format into
     *             DICOM EffectiveEchoTimeField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_EffectiveEchoTimeField
     */
    virtual ClassType get_class_type() const
            { return ECT_EffectiveEchoTimeField; }

protected:
    /// Create an instance of EffectiveEchoTimeField
    EffectiveEchoTimeField();

private:

};

} // namespace translator

} // namespace dicomifier

#include "EffectiveEchoTimeField.txx"

#endif // _4cdc3427_f5a6_4bd1_9453_6a278de4f93b
