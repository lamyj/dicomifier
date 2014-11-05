/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SubjectsTreeItemData.h"

namespace dicomifier
{

namespace ihm
{

SubjectsTreeItemData
::SubjectsTreeItemData(dicomifier::bruker::BrukerDataset *brukerDataset)
{
    this->_name = brukerDataset->GetFieldData("SUBJECT_name_string")->get_string(0);
    this->_study = brukerDataset->GetFieldData("SUBJECT_study_name")->get_string(0);
    this->_date = ""; // TODO
}

SubjectsTreeItemData
::~SubjectsTreeItemData()
{
    // Nothing to do
}

std::string
SubjectsTreeItemData
::get_name() const
{
    return this->_name;
}

std::string
SubjectsTreeItemData
::get_study() const
{
    return this->_study;
}

std::string
SubjectsTreeItemData
::get_date() const
{
    return this->_date;
}

} // namespace ihm

} // namespace dicomifier
