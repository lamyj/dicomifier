/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _19bfa5bd_cd2d_4141_ae2a_237444f2589b
#define _19bfa5bd_cd2d_4141_ae2a_237444f2589b

#include <QDate>
#include <QList>
#include <QVariant>

#include "bruker/BrukerDataset.h"

namespace dicomifier
{

namespace gui
{

class TreeItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

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
    std::string get_subjectDirectory() const { return this->_subjectDirectory; }
    std::string get_study() const { return this->_study; }
    std::string get_series() const { return this->_series; }
    std::string get_reconstruction() const { return this->_reconstruction; }
    std::string get_date() const { return this->_date; }
    std::string get_directory() const { return this->_directory; }
    std::string get_seriesDirectory() const { return this->_seriesDirectory; }
    std::string get_recoDirectory() const { return this->_recoDirectory; }
    std::string get_protocolName() const { return this->_protocolName; }
    QDateTime get_qdatetime() const { return this->_qdatetime; }

    std::string get_DicomErrorMsg() const { return this->_DicomErrorMsg; }
    std::string get_StoreErrorMsg() const { return this->_StoreErrorMsg; }
    std::string get_DicomdirErrorMsg() const { return this->_DicomdirErrorMsg; }
    std::string get_ZipErrorMsg() const { return this->_ZipErrorMsg; }

    std::string get_destinationDirectory() const { return this->_destinationDirectory; }

    void set_name(std::string const & name) { this->_name = name; }
    void set_study(std::string const & study) { this->_study = study; }
    void set_series(std::string const & series) { this->_series = series; }

    void set_subjectDirectory(std::string const & subjectDirectory)
            { this->_subjectDirectory = subjectDirectory; }
    void set_data(const QList<QVariant> & data) { this->_itemData = data; }
    void set_parent(TreeItem* parent) { this->_parentItem = parent; }
    void set_directory(std::string const & directory)
            { this->_directory = directory; }
    void set_seriesDirectory(std::string const & seriesDirectory)
            { this->_seriesDirectory = seriesDirectory; }
    void set_recoDirectory(std::string const & recoDirectory)
            { this->_recoDirectory = recoDirectory; }

    void set_DicomErrorMsg(std::string const & dicomerrormsg)
            { this->_DicomErrorMsg = dicomerrormsg; }
    void set_StoreErrorMsg(std::string const & storeerrormsg)
            { this->_StoreErrorMsg = storeerrormsg; }
    void set_DicomdirErrorMsg(std::string const & message) { this->_DicomdirErrorMsg = message; }
    void set_ZipErrorMsg(std::string const & message) { this->_ZipErrorMsg = message; }

    void set_destinationDirectory(std::string const & destination)
            { this->_destinationDirectory = destination; }

    void fill_data(dicomifier::bruker::BrukerDataset* const brukerdataset);

    void setEnabled(bool enabled)
    {
        this->_enabled = enabled;
        emit enabledChanged(enabled);
    }

    bool isEnabled() const
    { return this->_enabled; }

signals:
    void SendDate(double date);

    void enabledChanged(bool enabled);

private:
    QList<TreeItem*> _childItems;
    QList<QVariant>  _itemData;
    TreeItem *       _parentItem;
    Qt::CheckState   _checkState;

    std::string _name;
    std::string _subjectDirectory;
    std::string _study;
    std::string _series;
    std::string _reconstruction;
    std::string _date;
    std::string _directory;
    std::string _seriesDirectory;
    std::string _recoDirectory;
    std::string _protocolName;
    QDateTime _qdatetime;

    std::string _DicomErrorMsg;
    std::string _StoreErrorMsg;
    std::string _DicomdirErrorMsg;
    std::string _ZipErrorMsg;

    std::string _destinationDirectory;

    bool _enabled;

};

} // namespace gui

} // namespace dicomifier

#endif // _19bfa5bd_cd2d_4141_ae2a_237444f2589b
