/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EnhanceBrukerDicom.h"

#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <odil/dcmtk/conversion.h>
#include <odil/Element.h>
#include <odil/json_converter.h>
#include <odil/registry.h>
#include <odil/Writer.h>

#include "bruker/Directory.h"
#include "bruker/json_converter.h"
#include "core/DicomifierException.h"
#include "javascript/JavascriptVM.h"

namespace dicomifier
{

namespace bruker
{

EnhanceBrukerDicom::EnhanceBrukerDicom()
: _brukerDir(""), _SOPClassUID(""), _outputDir("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(
    std::string const & brukerDir, std::string const & sopclassuid,
    std::string const & outputDir, std::string const & studyNumber,
    std::string const & seriesNumber):
    _brukerDir(brukerDir),
    _SOPClassUID(),
    _outputDir(outputDir), _studyNumber(studyNumber),
    _seriesNumber(seriesNumber)
{
    std::string uid;
    for(auto const & entry: odil::registry::uids_dictionary)
    {
        if(entry.second.name == sopclassuid || entry.second.keyword == sopclassuid)
        {
            uid = entry.first;
            break;
        }
    }
    if(uid.empty())
    {
        throw DicomifierException("Unknown SOP Class UID name");
    }

    this->_SOPClassUID = uid;
}

EnhanceBrukerDicom::~EnhanceBrukerDicom()
{
    // Nothing to do
}

std::string const &
EnhanceBrukerDicom
::get_brukerDir() const
{
    return this->_brukerDir;
}

void
EnhanceBrukerDicom
::set_brukerDir(std::string const & brukerDir)
{
    this->_brukerDir = brukerDir;
}

std::string const &
EnhanceBrukerDicom
::get_SOPClassUID() const
{
    return this->_SOPClassUID;
}

void
EnhanceBrukerDicom
::set_SOPClassUID(std::string const & sopclassuid)
{
    this->_SOPClassUID = sopclassuid;
}

const std::string &
EnhanceBrukerDicom
::get_outputDir() const
{
    return this->_outputDir;
}

void
EnhanceBrukerDicom
::set_outputDir(const std::string &outputDir)
{
    this->_outputDir = outputDir;
}

void
EnhanceBrukerDicom
::run() const
{
    std::stringstream streamstr;
    streamstr << "require('bruker2dicom/converter.js');\n"
              << "dicomifier.bruker2dicom.convert('" << this->_brukerDir
              << "', '" << this->_studyNumber
              << "', '" << this->_seriesNumber
              << "', '" << this->_SOPClassUID
              << "', '" << this->_outputDir << "');";

    javascript::JavascriptVM jsvm;
    jsvm.run(streamstr.str(), jsvm.get_context());
}

std::string
EnhanceBrukerDicom
::get_default_directory_name(boost::filesystem::path const & parentdirectory)
{
    if (! boost::filesystem::exists(parentdirectory))
    {
        return "1";
    }

    // Suppose we can't have more than 100000000 sub-directory
    for (int output = 1; output < 100000000; ++output)
    {
        std::stringstream pattern;
        pattern << output;

        bool find = true;

        boost::filesystem::directory_iterator it_end;
        for(boost::filesystem::directory_iterator it(parentdirectory.string());
            it != it_end; ++it)
        {
            std::string currentobj((*it).path().filename().c_str());
            if(currentobj.find(pattern.str().c_str()) == 0)
            {
                // we find a number already used
                find = false;
                break;
            }
        }
        if (find)
        {
            std::stringstream stream;
            stream << output;
            return stream.str();
        }
    }

    throw DicomifierException("Cannot find default directory name.");
}

void
EnhanceBrukerDicom
::replace_unavailable_char(std::string &text)
{
    std::stringstream stream;
    stream << std::uppercase << text;
    text = stream.str();
    /* iterate over all charaters */
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        unsigned char c = text.at(i);
        if (std::isalpha(c) && std::islower(c))
        {
            text[i] = std::toupper(c);
        }
        else if ((c != '_') && !std::isdigit(c) && !std::isalpha(c))
        {
            // char not allowed, replace by _
            text[i] = '_';
        }
    }
}

std::string
EnhanceBrukerDicom
::create_directory_name(int sizemax, const std::string &prefix,
                        const std::string &suffix)
{
    int size = sizemax - prefix.length() - 1; // 1 is for '_'
    std::string suffixmodif = suffix.substr(0, size);

    EnhanceBrukerDicom::replace_unavailable_char(suffixmodif);

    std::stringstream streamout;
    streamout << prefix << "_" << suffixmodif;
    return streamout.str();
}

} // namespace bruker

} // namespace dicomifier
