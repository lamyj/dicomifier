/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a35825b6_4de6_42d8_be1d_ab694108290c
#define _a35825b6_4de6_42d8_be1d_ab694108290c

#include "translator/filters/DateTimeFilter.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

/**
 * @brief The DateTimeFilterCreator class
 */
class DateTimeFilterCreator : public TranslationCreatorBase
{
public:
    typedef DateTimeFilterCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of DateTimeFilterCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of DateTimeFilterCreator
    virtual ~DateTimeFilterCreator();

    /**
     * @brief Create Pointer to class DateTimeFilter
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new DateTimeFilter
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return DateTimeFilter
     */
    static std::string get_class_name() { return "DateTimeFilter"; }

protected:
    /// Create an instance of DateTimeFilterCreator
    DateTimeFilterCreator();

private:
    DateTimeFilterCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDateTimeFilterCreator
    {
        std::string outputformat;
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer datetimefilter;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _a35825b6_4de6_42d8_be1d_ab694108290c
