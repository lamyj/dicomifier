#ifndef SUBJECTSTREEITEMDATA_H
#define SUBJECTSTREEITEMDATA_H

#include <string>

#include "bruker/BrukerDataset.h"

class SubjectsTreeItemData
{
public:
    SubjectsTreeItemData(dicomifier::bruker::BrukerDataset * brukerDataset);
    ~SubjectsTreeItemData();

    std::string get_name() const;
    std::string get_study() const;
    std::string get_date() const;

private:
    std::string _name;
    std::string _study;
    std::string _date;

};

#endif // SUBJECTSTREEITEMDATA_H
