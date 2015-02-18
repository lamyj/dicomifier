/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <ctime>

#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/date_time/format_date_parser.hpp>
#include <boost/date_time/local_time/local_time.hpp>

#include "DateTimeFilter.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DateTimeFilter<VR>::Pointer
DateTimeFilter<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename DateTimeFilter<VR>::Pointer
DateTimeFilter<VR>
::New(Tag::Pointer tag, std::string const & outputformat)
{
    return Pointer(new Self(tag, outputformat));
}

template<DcmEVR VR>
DateTimeFilter<VR>
::DateTimeFilter()
    :SubTag<VR>(), _tag(NULL), _outputFormat("")
{
    // Nothing to do
}

template<DcmEVR VR>
DateTimeFilter<VR>
::DateTimeFilter(Tag::Pointer tag, std::string const & outputformat)
    :SubTag<VR>(), _tag(tag), _outputFormat(outputformat)
{
    // Nothing to do
}

template<DcmEVR VR>
DateTimeFilter<VR>
::~DateTimeFilter()
{
    // Nothing to do
}

template<DcmEVR VR>
void
DateTimeFilter<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (this->_tag == NULL)
    {
        throw DicomifierException("Cannot run DateTimeFilter.");
    }

    this->_array.clear();

    typename SubTag<VR>::Pointer subtag =
        std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

    subtag->run(brukerdataset, generator, dataset);

    auto array = subtag->get_array();

    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<VR>::toString(array[i]);;

        std::string test = temp;
        boost::replace_all(test, ",", ".");

        boost::local_time::local_date_time ldt(boost::local_time::not_a_date_time);

        // Try with ISO 8601 format: YYYY-MM-DDTHH:MM:SS,mmm+XXZZ
        if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
        {
            boost::local_time::local_time_input_facet *input_facet
                = new boost::local_time::local_time_input_facet("%Y-%m-%dT%H:%M:%S%f%q");

            // Set up the input datetime format.
            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), input_facet));
            ss.str(test);

            // Read a time into ldt
            ss >> ldt;
        }
        // Try with ParaVision 5 format: HH:MM:SS DD Mon YYYY
        if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
        {
            boost::local_time::local_time_input_facet *input_facet
                = new boost::local_time::local_time_input_facet("%H:%M:%S %d %b %Y");

            // Set up the input datetime format.
            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), input_facet));
            ss.str(test);

            // Read a time into ldt
            ss >> ldt;
        }
        // Format not recognized
        if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
        {
            std::stringstream stream;
            stream << "Bad value for Date-Time: " << temp;
            throw DicomifierException(stream.str());
        }

        boost::local_time::local_time_facet* output_facet =
                new boost::local_time::local_time_facet(this->_outputFormat.c_str());
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), output_facet));
        stream << ldt;

        this->_array.push_back(ElementTraits<VR>::fromString(stream.str()));
    }
}

} // namespace translator
    
} // namespace dicomifier
