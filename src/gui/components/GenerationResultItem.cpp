/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "GenerationResultItem.h"

namespace dicomifier
{

namespace gui
{

GenerationResultItem
::GenerationResultItem():
    _subjectName(""), _resultDirectory(""),
    _dicomdirCreation(GenerationResultItem::Result::None),
    _zipCreation(GenerationResultItem::Result::None),
    _DicomdirErrorMsg(""), _ZipErrorMsg("")
{
    // Nothing to do
}

GenerationResultItem
::~GenerationResultItem()
{
    // Nothing to do
}

std::string
GenerationResultItem
::resultToString(const GenerationResultItem::Result result)
{
    if (result == GenerationResultItem::Result::None)
        return "";
    else if (result == GenerationResultItem::Result::OK)
        return "OK";
    else if (result == GenerationResultItem::Result::Fail)
        return "Fail";
    else if (result == GenerationResultItem::Result::Canceled)
        return "Canceled";

    return "";
}

std::string
GenerationResultItem
::get_dicomdirCreationToString() const
{
    return GenerationResultItem::resultToString(this->_dicomdirCreation);
}

std::string
GenerationResultItem
::get_zipCreationToString() const
{
    return GenerationResultItem::resultToString(this->_zipCreation);
}

} // namespace gui

} // namespace dicomifier
