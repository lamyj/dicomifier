/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SubjectsTreeModel.h"
#include "core/Logger.h"

namespace dicomifier
{

namespace gui
{

SubjectsTreeModel
::SubjectsTreeModel(bool displaySubject, QObject *parent) :
    TreeModel(parent),
    _displaySubject(displaySubject)
{
    QList<QVariant> rootData;
    rootData << "Select" << "Name" << "Directory" << "Date";
    this->_rootItem->set_data(rootData);
}


void
SubjectsTreeModel
::Initialize(std::map<std::string, std::vector<TreeItem *> > dataList)
{
    this->_datalist = dataList;

    for (auto iter = this->_datalist.begin();
         iter != this->_datalist.end();
         iter++)
    {
        QList<QVariant> columnData;
        columnData << "";
        columnData << QString(iter->first.c_str());
        columnData << "";
        columnData << "";
        TreeItem * item = new TreeItem(this->_rootItem);
        item->set_data(columnData);

        for (auto iterdata : iter->second)
        {
            QList<QVariant> data;
            data << "";
            data << QString(this->_displaySubject ? iterdata->get_study().c_str() :
                                                    iterdata->get_name().c_str());
            data << QString(iterdata->get_subjectDirectory().c_str());
            data << QString(iterdata->get_date().c_str());

            iterdata->set_data(data);
            iterdata->set_parent(item);
            item->appendChild(iterdata);
        }

        item->update_from_child(Qt::Unchecked);
        this->_rootItem->appendChild(item);
    }
}

void
SubjectsTreeModel
::set_displaySubject(bool displaySubject)
{
    this->_displaySubject = displaySubject;
}

} // namespace gui

} // namespace dicomifier
