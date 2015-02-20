/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PreferencesFrame.h"
#include "ui_PreferencesFrame.h"

#include <QSettings>

namespace dicomifier
{

namespace gui
{

PreferencesFrame
::PreferencesFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::PreferencesFrame),
    _configFrame(NULL)
{
    this->_ui->setupUi(this);

    // Create TreeView
    this->_treeView = new PACSTreeView(this->_ui->widget);
    this->_treeView->Initialize();

    // Link Signals and Slots
    connect(this->_treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(TreeViewClicked(QModelIndex)));
}

PreferencesFrame
::~PreferencesFrame()
{
    if (this->_configFrame != NULL)
    {
        delete this->_configFrame;
        this->_configFrame = NULL;
    }

    // TreeView is destroy by deleting _ui

    delete this->_ui;
}

void
PreferencesFrame
::Initialize()
{
    // Initialize treeView
    this->_treeView->Initialize();
    TreeViewClicked(QModelIndex());

    // Initialize frame
    BaseFrame::Initialize();
}

void
PreferencesFrame
::Reset()
{
    // Nothing to do
}

void
PreferencesFrame
::SavePreferences()
{
    if (this->_treeView != NULL)
    {
        this->_treeView->SaveData();
    }
}

void
PreferencesFrame
::onUpdate_Preferences()
{
    // Nothing to do
}

void
PreferencesFrame
::TreeViewClicked(QModelIndex index)
{
    bool selected = index.isValid();

    // Edit and Delete button only enabled when treeItem is selected
    this->_ui->EditButton->setEnabled(selected);
    this->_ui->DeleteButton->setEnabled(selected);
}

void
PreferencesFrame
::modify_nextButton_enabled()
{
    // Always enabled
    this->update_nextButton(true);
}

void
PreferencesFrame
::modify_previousButton_enabled()
{
    // Always enabled
    this->update_previousButton(true);
}

void
PreferencesFrame
::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        // Resize the treeView (expand)
        this->_treeView->resize(this->_ui->widget->size());
    }

    QWidget::paintEvent(event);
}

void
PreferencesFrame
::on_NewButton_clicked()
{
    if (this->_configFrame != NULL)
    {
        delete this->_configFrame;
    }
    this->_configFrame = new PACSConfigurationFrame((QWidget*)this->parent());
    connect(this->_configFrame, SIGNAL(SendItem(PACSTreeItem*)),
            this->_treeView, SLOT(receiveNewItem(PACSTreeItem*)));
    this->_configFrame->setModal(true);
    this->_configFrame->show();
}

void
PreferencesFrame
::on_EditButton_clicked()
{
    if (this->_treeView != NULL && this->_treeView->currentIndex().isValid())
    {
        if (this->_configFrame != NULL)
        {
            delete this->_configFrame;
        }
        this->_configFrame = new PACSConfigurationFrame((QWidget*)this->parent());
        this->_configFrame->Initialize(this->_treeView->currentIndex());
        connect(this->_configFrame, SIGNAL(SendItem(PACSTreeItem*)),
                this->_treeView, SLOT(receiveNewItem(PACSTreeItem*)));
        this->_configFrame->setModal(true);
        this->_configFrame->show();
    }
}

void
PreferencesFrame
::on_DeleteButton_clicked()
{
    if (this->_treeView != NULL)
    {
        this->_treeView->DeleteSelectedItem();
    }
}

} // namespace gui

} // namespace dicomifier
