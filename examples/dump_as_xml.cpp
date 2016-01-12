/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <fstream>
#include <iostream>
#include <memory>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include <odil/DataSet.h>
#include <odil/Reader.h>
#include <odil/xml_converter.h>

int main(int argc, char** argv)
{
    for(int i=1; i<argc; ++i)
    {
        std::ifstream stream(argv[i], std::ios::in | std::ios::binary);

        std::pair<odil::DataSet, odil::DataSet> file;
        try
        {
            file = odil::Reader::read_file(stream);
        }
        catch(std::exception & e)
        {
            std::cout << "Could not read " << argv[i] << ": " << e.what() << "\n";
            continue;
        }

        auto const xml = odil::as_xml(file.second);

        std::stringstream xmldataset;
#if BOOST_VERSION >= 105600
        boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
#else
        boost::property_tree::xml_writer_settings<char> settings(' ', 4);
#endif
        boost::property_tree::write_xml(xmldataset, xml, settings);

        std::cout << xmldataset.str() << std::endl;
    }

    return EXIT_SUCCESS;
}
