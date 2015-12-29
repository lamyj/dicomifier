/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <boost/property_tree/xml_parser.hpp>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Reader.h>
#include <dcmtkpp/xml_converter.h>

int main(int argc, char** argv)
{
    for(int i=1; i<argc; ++i)
    {
        std::ifstream stream(argv[i], std::ios::in | std::ios::binary);

        std::pair<dcmtkpp::DataSet, dcmtkpp::DataSet> file;
        try
        {
            file = dcmtkpp::Reader::read_file(stream);
        }
        catch(std::exception & e)
        {
            std::cout << "Could not read " << argv[i] << ": " << e.what() << "\n";
            continue;
        }

        auto const xml = dcmtkpp::as_xml(file.second);

        std::stringstream xmldataset;
        boost::property_tree::xml_writer_settings<char> settings(' ', 4);
        boost::property_tree::write_xml(xmldataset, xml, settings);

        std::cout << xmldataset.str() << std::endl;
    }

    return EXIT_SUCCESS;
}
