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

/**
 * @brief The TreeItem class
 */
class TreeItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    /**
     * @brief Create an instance of TreeItem
     * @param parent: item containing this TreeItem
     * @param copy: copy the values
     */
    TreeItem(TreeItem * parent = 0, TreeItem * copy = NULL);

    /// Destroy the instance of TreeItem
    virtual ~TreeItem();

    /**
     * @brief Add a child item
     * @param child: child to append
     */
    void appendChild(TreeItem * child);

    /**
     * @brief Get child item from a given position
     * @param row: position of the child
     * @return child item
     */
    TreeItem * child(int row);

    /**
     * @brief Return number of child
     * @return childs count
     */
    int childCount() const;

    /**
     * @brief Return the number of column for this items
     * @return columns count
     */
    int columnCount() const;

    /**
     * @brief Get the data for a given column
     * @param column: position of the column
     * @return column value
     */
    QVariant data(int column) const;

    /**
     * @brief Return the position of this child in his parent
     * @return this position
     */
    int row() const;

    /**
     * @brief Return the parent item
     * @return _parent
     */
    TreeItem * parent();

    /// Return check State
    Qt::CheckState get_checkState() const;

    /// Modify check State
    void set_checkState(Qt::CheckState value);

    /// Compute the check state and update child and parent
    void update_checkState();

    /**
     * @brief Update this state after child modification
     * @param childstate: modified child state
     */
    void update_from_child(Qt::CheckState childstate);

    /**
     * @brief Update this state after parent modification
     * @param parentState: modified parent state
     */
    void update_from_parent(Qt::CheckState parentState);

    std::string get_name() const { return this->_name; }
    std::string get_subjectDirectory() const { return this->_subjectDirectory; }
    std::string get_study() const { return this->_study; }
    std::string get_series() const { return this->_series; }
    std::string get_reconstruction() const { return this->_reconstruction; }
    std::string get_date() const { return this->_date; }
    std::string get_acquisitionDate() const { return this->_acquisitionDate; }
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
    void set_DicomdirErrorMsg(std::string const & message)
            { this->_DicomdirErrorMsg = message; }
    void set_ZipErrorMsg(std::string const & message) { this->_ZipErrorMsg = message; }

    void set_destinationDirectory(std::string const & destination)
            { this->_destinationDirectory = destination; }

    /**
     * @brief Initialize item with bruker dataset
     * @param brukerdataset: dataset containing item values
     */
    void fill_data(dicomifier::bruker::BrukerDataset* const brukerdataset);

    bool compareTo(TreeItem * other) const;

    /***************************************************************
     * Accessors for Property Enabled
     **************************************************************/
    void setEnabled(bool enabled)
    {
        this->_enabled = enabled;
        emit enabledChanged(enabled);
    }

    bool isEnabled() const { return this->_enabled; }

signals:
    /**
     * @brief Signal emit to send Date to SubjectsFrame
     * @param date: date to send
     */
    void SendDate(double date);

    /***************************************************************
     * Event for Property Enabled
     **************************************************************/
    void enabledChanged(bool enabled);

private:
    /// Childs
    QList<TreeItem*> _childItems;

    /// Values
    QList<QVariant>  _itemData;

    /// Parent
    TreeItem *       _parentItem;

    /// Check State (item is checkable and contain a checkbox as first column)
    Qt::CheckState   _checkState;

    /// Subject Name
    std::string _name;

    /// Bruker subject directory
    std::string _subjectDirectory;

    /// Study Name
    std::string _study;

    /// Series Name
    std::string _series;

    /// Reconstruction Name
    std::string _reconstruction;

    /// Study creation date
    std::string _date;

    /// Record creation date
    std::string _acquisitionDate;

    ///
    std::string _directory;

    /// Bruker series directory
    std::string _seriesDirectory;

    /// Bruker reconstruction directory
    std::string _recoDirectory;

    /// Protocol Name
    std::string _protocolName;

    /// Record creation date
    QDateTime _qdatetime;

    /// Error message for DICOM creation
    std::string _DicomErrorMsg;

    /// Error message for Store action
    std::string _StoreErrorMsg;

    /// Error message for DICOMDIR creation
    std::string _DicomdirErrorMsg;

    /// Error message for ZIP creation
    std::string _ZipErrorMsg;

    /// Dicomifier output directory
    std::string _destinationDirectory;

    /***************************************************************
     * Property Enabled
     **************************************************************/
    bool _enabled;

};

} // namespace gui

} // namespace dicomifier

#endif // _19bfa5bd_cd2d_4141_ae2a_237444f2589b
