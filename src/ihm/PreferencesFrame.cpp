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

namespace ihm
{

PreferencesFrame
::PreferencesFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::PreferencesFrame)
{
    this->_ui->setupUi(this);

    QStringList itemslist;
    itemslist << "MRI Multi Frames";
    itemslist << "MRI Single Frame";
    this->_ui->comboBox->addItems(itemslist);
}

PreferencesFrame
::~PreferencesFrame()
{
    delete this->_ui;
}

void
PreferencesFrame
::Initialize()
{
    QSettings settings;
    this->_ui->lineEdit->setText(settings.value(QString("Input/directory"), QString("")).toString());
    this->_ui->lineEdit_2->setText(settings.value(QString("Output/directory"), QString("")).toString());
    this->_ui->comboBox->setCurrentIndex(settings.value(QString("Output/dicomformat"), 0).toInt());

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
    QSettings settings;

    settings.beginGroup(QString("Input"));
    settings.setValue(QString("directory"), this->_ui->lineEdit->text());
    settings.endGroup();

    settings.beginGroup(QString("Output"));
    settings.setValue(QString("directory"), this->_ui->lineEdit_2->text());
    settings.setValue(QString("dicomformat"), this->_ui->comboBox->currentIndex());
    settings.endGroup();
}

void
PreferencesFrame
::modify_nextButton_enabled()
{
    emit this->update_nextButton(true);
}

void
PreferencesFrame
::modify_previousButton_enabled()
{
    emit this->update_previousButton(true);
}

} // namespace ihm

} // namespace dicomifier
