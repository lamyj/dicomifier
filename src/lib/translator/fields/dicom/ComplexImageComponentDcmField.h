/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _190730b0_3e54_4c0d_8ddd_897a8e803a29
#define _190730b0_3e54_4c0d_8ddd_897a8e803a29

#include "translator/SubTag.h"

namespace dicomifier
{

namespace translator
{

/**
 * @brief The ComplexImageComponentDcmField class
 */
template<DcmEVR VR>
class ComplexImageComponentDcmField : public SubTag<VR>
{
public:
    typedef ComplexImageComponentDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of ComplexImageComponentDcmField
    static Pointer New();

    /// Destroy the instance of ComplexImageComponentDcmField
    virtual ~ComplexImageComponentDcmField();

    /**
     * @brief run: Convert Bruker ComplexImageComponentDcmField format into
     *             DICOM ComplexImageComponentDcmField format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_ComplexImageComponentDcmField
     */
    virtual ClassType get_class_type() const
            { return ECT_ComplexImageComponentDcmField; }

protected:
    /// Create an instance of ComplexImageComponentDcmField
    ComplexImageComponentDcmField();

private:

};

} // namespace translator

} // namespace dicomifier

#include "ComplexImageComponentDcmField.txx"

#endif // _190730b0_3e54_4c0d_8ddd_897a8e803a29
