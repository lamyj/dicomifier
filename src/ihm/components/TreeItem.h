/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _19bfa5bd_cd2d_4141_ae2a_237444f2589b
#define _19bfa5bd_cd2d_4141_ae2a_237444f2589b

#include <QList>
#include <QVariant>

#include "bruker/BrukerDataset.h"

namespace dicomifier
{

namespace ihm
{

class TreeItem
{
public:
    TreeItem(TreeItem * parent = 0, TreeItem * copy = NULL);
    virtual ~TreeItem();

    void appendChild(TreeItem * child);

    TreeItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem * parent();

    Qt::CheckState get_checkState() const;
    void set_checkState(Qt::CheckState value);
    void update_checkState();

    void update_from_child(Qt::CheckState childstate);
    void update_from_parent(Qt::CheckState parentState);

    std::string get_name() const { return this->_name; }
    std::string get_study() const { return this->_study; }
    std::string get_series() const { return this->_series; }
    std::string get_reconstruction() const { return this->_reconstruction; }
    std::string get_date() const { return this->_date; }
    std::string get_directory() const { return this->_directory; }
    std::string get_seriesDirectory() const { return this->_seriesDirectory; }
    std::string get_recoDirectory() const { return this->_recoDirectory; }

    void set_data(const QList<QVariant> & data) { this->_itemData = data; }
    void set_parent(TreeItem* parent) { this->_parentItem = parent; }
    void set_directory(std::string const & directory)
            { this->_directory = directory; }
    void set_seriesDirectory(std::string const & seriesDirectory)
            { this->_seriesDirectory = seriesDirectory; }
    void set_recoDirectory(std::string const & recoDirectory)
            { this->_recoDirectory = recoDirectory; }

    void fill_data(dicomifier::bruker::BrukerDataset* const brukerdataset);

private:
    QList<TreeItem*> _childItems;
    QList<QVariant>  _itemData;
    TreeItem *       _parentItem;
    Qt::CheckState   _checkState;

    std::string _name;
    std::string _study;
    std::string _series;
    std::string _reconstruction;
    std::string _date;
    std::string _directory;
    std::string _seriesDirectory;
    std::string _recoDirectory;

};

} // namespace ihm

} // namespace dicomifier

#endif // _19bfa5bd_cd2d_4141_ae2a_237444f2589b
