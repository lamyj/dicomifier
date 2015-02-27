/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <ctime>

#include "core/Hashcode.h"
#include "TreeItem.h"

namespace dicomifier
{

namespace gui
{

TreeItem
::TreeItem(TreeItem *parent, TreeItem * copy):
    _parentItem(parent), _checkState(Qt::Unchecked),
    _name(""), _subjectDirectory(""), _study(""), _series(""),
    _reconstruction(""), _date(""), _acquisitionDate(""), _directory(""),
    _seriesDirectory(""), _recoDirectory(""), _protocolName(""),
    _qdatetime(QDateTime::currentDateTime()), _enabled(true),
    _DicomErrorMsg("Canceled"), _StoreErrorMsg(""),
    _DicomdirErrorMsg(""), _ZipErrorMsg(""), _destinationDirectory("")
{
    if (copy != NULL)
    {
        this->_name            = copy->get_name();
        this->_subjectDirectory= copy->get_subjectDirectory();
        this->_study           = copy->get_study();
        this->_series          = copy->get_series();
        this->_reconstruction  = copy->get_reconstruction();
        this->_date            = copy->get_date();
        this->_acquisitionDate = copy->get_acquisitionDate();
        this->_directory       = copy->get_directory();
        this->_seriesDirectory = copy->get_seriesDirectory();
        this->_recoDirectory   = copy->get_recoDirectory();
        this->_protocolName    = copy->get_protocolName();
        this->_qdatetime       = copy->get_qdatetime();
        this->_enabled         = copy->isEnabled();
        this->_DicomErrorMsg   = copy->get_DicomErrorMsg();
        this->_StoreErrorMsg   = copy->get_StoreErrorMsg();
        this->_DicomdirErrorMsg= copy->get_DicomdirErrorMsg();
        this->_ZipErrorMsg     = copy->get_ZipErrorMsg();
        this->_destinationDirectory= copy->get_destinationDirectory();

        this->set_checkState(copy->get_checkState());
    }
}

TreeItem
::~TreeItem()
{
    qDeleteAll(this->_childItems);
}

void
TreeItem
::appendChild(TreeItem *child)
{
    if (child != NULL)
    {
        this->_childItems.append(child);
    }
}

TreeItem *
TreeItem
::child(int row)
{
    return this->_childItems.value(row);
}

int
TreeItem
::childCount() const
{
    return this->_childItems.count();
}

int
TreeItem
::columnCount() const
{
    return this->_itemData.count();
}

QVariant
TreeItem
::data(int column) const
{
    return this->_itemData.value(column);
}

int
TreeItem
::row() const
{
    if (this->_parentItem != NULL)
    {
        return this->_parentItem->_childItems.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}

TreeItem *
TreeItem
::parent()
{
    return this->_parentItem;
}

Qt::CheckState
TreeItem
::get_checkState() const
{
    return this->_checkState;
}

void
TreeItem
::set_checkState(Qt::CheckState value)
{
    this->_checkState = value;
}

void
TreeItem
::update_checkState()
{
    switch (this->_checkState)
    {
    case Qt::Checked:
    {
        this->set_checkState(Qt::Unchecked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Unchecked);
        }
        break;
    }

    case Qt::PartiallyChecked:
    {
        this->set_checkState(Qt::Checked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Checked);
        }
        break;
    }

    case Qt::Unchecked:
    {
        this->set_checkState(Qt::Checked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Checked);
        }
        break;
    }

    default:
    {
        this->set_checkState(Qt::Unchecked);
        break;
    }
    }

    if (this->_parentItem != NULL && this->_parentItem != this)
    {
        this->_parentItem->update_from_child(this->get_checkState());
    }
}

void
TreeItem
::update_from_child(Qt::CheckState childstate)
{
    bool oneselected = false;
    bool oneunselected = false;

    for (auto child : this->_childItems)
    {
        if (child->get_checkState() == Qt::Unchecked)
        {
            oneunselected = true;
        }
        else
        {
            oneselected = true;
        }
    }

    // Not all selected
    if (oneselected && oneunselected)
    {
        this->_checkState = Qt::PartiallyChecked;
    }
    // All selected
    else if (oneselected)
    {
        this->_checkState = Qt::Checked;
    }
    // All unselected
    else
    {
        this->_checkState = Qt::Unchecked;
    }
}

void
TreeItem
::update_from_parent(Qt::CheckState parentState)
{
    if (this->isEnabled())
    {
        this->_checkState = parentState;
    }
}

std::string
TreeItem
::get_name() const
{
    return this->_name;
}

std::string
TreeItem
::get_subjectDirectory() const
{
    return this->_subjectDirectory;
}

std::string TreeItem::get_study() const
{
    return this->_study;
}

std::string
TreeItem
::get_series() const
{
    return this->_series;
}

std::string
TreeItem
::get_reconstruction() const
{
    return this->_reconstruction;
}

std::string
TreeItem
::get_date() const
{
    return this->_date;
}

std::string
TreeItem
::get_acquisitionDate() const
{
    return this->_acquisitionDate;
}

std::string
TreeItem
::get_directory() const
{
    return this->_directory;
}

std::string
TreeItem
::get_seriesDirectory() const
{
    return this->_seriesDirectory;
}

std::string
TreeItem
::get_recoDirectory() const
{
    return this->_recoDirectory;
}

std::string
TreeItem
::get_protocolName() const
{
    return this->_protocolName;
}

QDateTime
TreeItem
::get_qdatetime() const
{
    return this->_qdatetime;
}

std::string
TreeItem
::get_DicomErrorMsg() const
{
    return this->_DicomErrorMsg;
}

std::string
TreeItem
::get_StoreErrorMsg() const
{
    return this->_StoreErrorMsg;
}

std::string
TreeItem
::get_DicomdirErrorMsg() const
{
    return this->_DicomdirErrorMsg;
}

std::string
TreeItem
::get_ZipErrorMsg() const
{
    return this->_ZipErrorMsg;
}

std::string
TreeItem
::get_destinationDirectory() const
{
    return this->_destinationDirectory;
}

void
TreeItem
::set_name(const std::string &name)
{
    this->_name = name;
}

void
TreeItem
::set_study(const std::string &study)
{
    this->_study = study;
}

void
TreeItem
::set_series(const std::string &series)
{
    this->_series = series;
}

void
TreeItem
::set_subjectDirectory(const std::string &subjectDirectory)
{
    this->_subjectDirectory = subjectDirectory;
}

void
TreeItem
::set_data(const QList<QVariant> &data)
{
    this->_itemData = data;
}

void
TreeItem
::set_parent(TreeItem *parent)
{
    this->_parentItem = parent;
}

void
TreeItem
::set_directory(const std::string &directory)
{
    this->_directory = directory;
}

void
TreeItem
::set_seriesDirectory(const std::string &seriesDirectory)
{
    this->_seriesDirectory = seriesDirectory;
}

void
TreeItem
::set_recoDirectory(const std::string &recoDirectory)
{
    this->_recoDirectory = recoDirectory;
}

void
TreeItem
::set_DicomErrorMsg(const std::string &dicomerrormsg)
{
    this->_DicomErrorMsg = dicomerrormsg;
}

void
TreeItem
::set_StoreErrorMsg(const std::string &storeerrormsg)
{
    this->_StoreErrorMsg = storeerrormsg;
}

void
TreeItem
::set_DicomdirErrorMsg(const std::string &message)
{
    this->_DicomdirErrorMsg = message;
}

void
TreeItem
::set_ZipErrorMsg(const std::string &message)
{
    this->_ZipErrorMsg = message;
}

void
TreeItem
::set_destinationDirectory(const std::string &destination)
{
    this->_destinationDirectory = destination;
}

void
TreeItem
::fill_data(bruker::Dataset const &brukerdataset)
{
    if (brukerdataset.has_field("SUBJECT_name_string"))
    {
        this->_name = brukerdataset.get_field("SUBJECT_name_string").get_string(0);
    }

    if (brukerdataset.has_field("SUBJECT_study_name"))
    {
        this->_study = brukerdataset.get_field("SUBJECT_study_name").get_string(0);
    }

    if (brukerdataset.has_field("SUBJECT_abs_date"))
    {
        float datestr = 0;
        // Be carefull: Difference between PV5 et PV6
        auto field = brukerdataset.get_field("SUBJECT_abs_date");

        datestr = field.get_float(0);

        std::time_t now = datestr;
        tm *ltm = localtime(&now);

        char format[64];
        memset(&format[0], 0, 64);
        strftime(format, 64, "%d / %m / %Y %H:%M:%S", ltm);

        this->_date = std::string(&format[0]);
        this->_qdatetime = QDateTime(QDate(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday),
                                     QTime(ltm->tm_hour, ltm->tm_min, ltm->tm_sec));

        this->SendDate(datestr);
    }

    if (brukerdataset.has_field("Method"))
    {
        this->_series = brukerdataset.get_field("Method").get_string(0);
    }

    if (brukerdataset.has_field("RECO_mode"))
    {
        this->_reconstruction = brukerdataset.get_field("RECO_mode").get_string(0);
    }

    if (brukerdataset.has_field("VisuAcquisitionProtocol"))
    {
        this->_protocolName = brukerdataset.get_field("VisuAcquisitionProtocol").get_string(0);
    }

    if (brukerdataset.has_field("VisuSubjectId"))
    {
        this->_destinationDirectory = brukerdataset.get_field("VisuSubjectId").get_string(0);
        this->_destinationDirectory =
                dicomifier::hashcode::hashToString(dicomifier::hashcode::hashCode(this->_destinationDirectory));
    }

    if (brukerdataset.has_field("VisuAcqDate"))
    {
        std::string acqdate = brukerdataset.get_field("VisuAcqDate").get_string(0);

        struct tm parts = {0};
        strptime(acqdate.c_str(), "%H:%M:%S %d %b %Y", &parts);

        char format[64];
        memset(&format[0], 0, 64);
        strftime(format, 64, "%d / %m / %Y %H:%M:%S", &parts);

        std::string value(&format[0]);

        this->_acquisitionDate = value;
    }
}

bool
TreeItem
::operator ==(const TreeItem &other) const
{
    if (this->_name            == other.get_name() &&
        this->_subjectDirectory== other.get_subjectDirectory() &&
        this->_study           == other.get_study() &&
        this->_series          == other.get_series() &&
        this->_reconstruction  == other.get_reconstruction() &&
        this->_date            == other.get_date() &&
        this->_acquisitionDate == other.get_acquisitionDate() &&
        this->_directory       == other.get_directory() &&
        this->_seriesDirectory == other.get_seriesDirectory() &&
        this->_recoDirectory   == other.get_recoDirectory() &&
        this->_protocolName    == other.get_protocolName() &&
        this->_qdatetime       == other.get_qdatetime() &&
        this->_enabled         == other.isEnabled() &&
        this->_DicomErrorMsg   == other.get_DicomErrorMsg() &&
        this->_StoreErrorMsg   == other.get_StoreErrorMsg() &&
        this->_DicomdirErrorMsg== other.get_DicomdirErrorMsg() &&
        this->_ZipErrorMsg     == other.get_ZipErrorMsg() &&
        this->_destinationDirectory== other.get_destinationDirectory())
    {
        return true;
    }

    return false;
}

} // namespace gui

} // namespace dicomifier
