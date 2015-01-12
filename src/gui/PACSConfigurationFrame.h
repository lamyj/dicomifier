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
}

class PACSConfigurationFrame : public QDialog
{
    Q_OBJECT

public:
    explicit PACSConfigurationFrame(QWidget *parent = 0);
    ~PACSConfigurationFrame();

    void Initialize(QModelIndex const & selectedIndex);

signals:
    void SendItem(PACSTreeItem * item);

private slots:
    void on_AcceptButton_clicked();

    void onDataChanged();

    void on_pacsIdType_currentIndexChanged(int index);

    void on_TestButton_clicked();

private:

    Ui::PACSConfigurationFrame * _ui;
};

} // namespace gui

} // namespace dicomifier

#endif // PACSCONFIGURATIONFRAME_H
