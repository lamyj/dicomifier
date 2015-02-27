/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3516683e_bef5_491e_bcd7_c6648dce361c
#define _3516683e_bef5_491e_bcd7_c6648dce361c

#include "translator/SubTag.h"

namespace dicomifier
{

namespace translator
{

template<DcmEVR VR>
class DateTimeFilter : public SubTag<VR>
{
public:
    typedef DateTimeFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of DateTimeFilter
    static Pointer New();

    /**
     * @brief Create pointer to new instance of DateTimeFilter
     * @param tag: Bruker Date/Time field
     * @param outputformat: DateTime output format
     * @return new instance of DateTimeFilter
     */
    static Pointer New(Tag::Pointer tag, std::string const & outputformat);

    /// Destroy the instance of DateTimeFilter
    virtual ~DateTimeFilter();

    /**
     * @brief run: Convert Date-Time Bruker format into
     *             DICOM Date-Time format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);

protected:
    /// Create an instance of DateTimeFilter
    DateTimeFilter();

    /**
     * @brief Create an instance of DateTimeFilter
     * @param tag: Bruker Date/Time field
     * @param outputformat: DateTime output format
     */
    DateTimeFilter(Tag::Pointer tag, std::string const & outputformat);

private:
    /// Bruker Date/Time field
    Tag::Pointer _tag;

    /// DateTime output format
    std::string _outputFormat;

};

} // namespace translator

} // namespace dicomifier

#include "DateTimeFilter.txx"

#endif // _3516683e_bef5_491e_bcd7_c6648dce361c
