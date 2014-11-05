/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b9a2e777_85dd_48e8_9a70_15529b84a8a2
#define _b9a2e777_85dd_48e8_9a70_15529b84a8a2

#include <string>

#include "bruker/BrukerDataset.h"

namespace dicomifier
{

namespace ihm
{

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

} // namespace ihm

} // namespace dicomifier

#endif // _b9a2e777_85dd_48e8_9a70_15529b84a8a2
