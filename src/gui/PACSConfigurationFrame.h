/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef PACSCONFIGURATIONFRAME_H
#define PACSCONFIGURATIONFRAME_H

#include <QDialog>
#include <QModelIndex>

#include "components/PACSTreeItem.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class PACSConfigurationFrame;
} // namespace Ui

/**
 * @brief The PACSConfigurationFrame class
 */
class PACSConfigurationFrame : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of PACSConfigurationFrame
     * @param parent: widget containing the PACSConfigurationFrame
     */
    explicit PACSConfigurationFrame(QWidget *parent = 0);

    /// Destroy the instance of PACSConfigurationFrame
    ~PACSConfigurationFrame();

    /**
     * @brief Initialize the instance of PACSConfigurationFrame
     * @param selectedIndex: Selected item
     */
    void Initialize(QModelIndex const & selectedIndex);

signals:
    /**
     * @brief Signal emit to send new item to PreferencesFrame
     * @param item: item to send
     */
    void SendItem(PACSTreeItem * item);

private slots:
    /// Event triggered by clicking on Accept button
    void on_AcceptButton_clicked();

    /// Event triggered by changing any information on the frame
    void onDataChanged();

    /**
     * @brief Event triggered by changing Identity Type comboBox
     * @param index: selected index
     */
    void on_pacsIdType_currentIndexChanged(int index);

    /// Event triggered by clicking on Test button
    void on_TestButton_clicked();

private:
    /// User Interface
    Ui::PACSConfigurationFrame * _ui;

};

} // namespace gui

} // namespace dicomifier

#endif // PACSCONFIGURATIONFRAME_H
