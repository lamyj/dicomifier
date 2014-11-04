#include "SubjectsTreeItemData.h"

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
