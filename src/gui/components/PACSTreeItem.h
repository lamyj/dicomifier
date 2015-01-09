/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5eca9a1f_0e9d_4c49_bf4c_50443fb390f2
#define _5eca9a1f_0e9d_4c49_bf4c_50443fb390f2

#include <sstream>

#include <QObject>
#include <QVariant>

#include "dicom/SCU.h"

namespace dicomifier
{

namespace gui
{

QString const CONF_GROUP_PACS   = "pacs";
QString const CONF_KEY_NUMBER   = "number";
QString const CONF_KEY_NAME     = "name";
QString const CONF_KEY_ADDRESS  = "address";
QString const CONF_KEY_PORT     = "port";
QString const CONF_KEY_CALLER   = "caller";
QString const CONF_KEY_CALLED   = "called";
QString const CONF_KEY_IDENTITY = "identity";
QString const CONF_KEY_FIRST    = "first";
QString const CONF_KEY_SECOND   = "second";

class PACSTreeItem : public QObject
{
    Q_OBJECT

public:
    PACSTreeItem(PACSTreeItem * parent = 0, PACSTreeItem * copy = NULL);
    virtual ~PACSTreeItem();

    void extractData(PACSTreeItem * copy);

    void appendChild(PACSTreeItem * child);
    void set_data(const QList<QVariant> & data) { this->_itemData = data; }
    void set_parent(PACSTreeItem* parent) { this->_parentItem = parent; }

    void fill_data();

    PACSTreeItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    PACSTreeItem * parent();

    void set_name(std::string const & name) { this->_name = name; }
    void set_address(std::string const & address) { this->_address = address; }
    void set_port(std::string const & port) { this->_port = port; }
    void set_caller(std::string const & caller) { this->_caller = caller; }
    void set_called(std::string const & called) { this->_called = called; }
    void set_identityType(UserIdentityType const & idType) { this->_identityType = idType; }
    void set_idTypeFirst(std::string const & first) { this->_idTypeFirst = first; }
    void set_idTypeSecond(std::string const & second) { this->_idTypeSecond = second; }

    std::string get_name() const { return this->_name; }
    std::string get_address() const { return this->_address; }
    std::string get_port() const { return this->_port; }
    std::string get_caller() const { return this->_caller; }
    std::string get_called() const { return this->_called; }
    UserIdentityType get_identityType() const { return this->_identityType; }
    std::string get_idTypeFirst() const { return this->_idTypeFirst; }
    std::string get_idTypeSecond() const { return this->_idTypeSecond; }

protected:

private:
    QList<PACSTreeItem *> _childItems;
    QList<QVariant>       _itemData;
    PACSTreeItem *        _parentItem;

    std::string _name;
    std::string _address;
    std::string _port;
    std::string _caller;
    std::string _called;
    UserIdentityType _identityType;
    std::string _idTypeFirst;
    std::string _idTypeSecond;

};

} // namespace gui

} // namespace dicomifier

#endif // _5eca9a1f_0e9d_4c49_bf4c_50443fb390f2
