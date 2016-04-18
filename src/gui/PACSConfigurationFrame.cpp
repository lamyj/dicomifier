/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "PACSConfigurationFrame.h"
#include "ui_PACSConfigurationFrame.h"

#include <iostream>
#include <stdexcept>

#include <odil/Association.h>
#include <odil/registry.h>
#include <odil/EchoSCU.h>

namespace dicomifier
{

namespace gui
{

PACSConfigurationFrame
::PACSConfigurationFrame(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::PACSConfigurationFrame)
{
    this->_ui->setupUi(this);

    // Initialize ComboBox Authorization type
    // c.f. lib/dicom/SCU.h for Name
    QStringList itemslist;
    itemslist << "None";
    itemslist << "Username";
    itemslist << "Username And Password";
    itemslist << "Kerberos";
    itemslist << "SAML";

    this->_ui->pacsIdType->addItems(itemslist);
}

PACSConfigurationFrame
::~PACSConfigurationFrame()
{
    delete this->_ui;
}

void
PACSConfigurationFrame
::Initialize(const QModelIndex &selectedIndex)
{
    if (selectedIndex.isValid())
    {
        PACSTreeItem * item =
            static_cast<PACSTreeItem*>(selectedIndex.internalPointer());

        if (item != NULL)
        {
            this->_ui->pacsName->setText(QString(item->get_name().c_str()));
            this->_ui->pacsAddress->setText(QString(item->get_address().c_str()));
            this->_ui->pacsPort->setText(QString(item->get_port().c_str()));
            this->_ui->pacsCalled->setText(QString(item->get_called().c_str()));
            this->_ui->pacsCaller->setText(QString(item->get_caller().c_str()));
            this->_ui->pacsIdType->setCurrentIndex((int)item->get_identityType());
            this->_ui->pacsFrist->setText(QString(item->get_idTypeFirst().c_str()));
            this->_ui->pacsSecond->setText(QString(item->get_idTypeSecond().c_str()));
        }
    }
}

void
PACSConfigurationFrame
::on_AcceptButton_clicked()
{
    PACSTreeItem * item = new PACSTreeItem();

    item->set_name(this->_ui->pacsName->text().toStdString());
    item->set_address(this->_ui->pacsAddress->text().toStdString());
    item->set_port(this->_ui->pacsPort->text().toStdString());
    item->set_called(this->_ui->pacsCalled->text().toStdString());
    item->set_caller(this->_ui->pacsCaller->text().toStdString());
    if (this->_ui->pacsIdType->currentIndex() != -1)
    {
        item->set_identityType(this->_ui->pacsIdType->currentIndex());
        item->set_idTypeFirst(this->_ui->pacsFrist->text().toStdString());
        item->set_idTypeSecond(this->_ui->pacsSecond->text().toStdString());
    }
    else
    {
        item->set_identityType(0);
        item->set_idTypeFirst("");
        item->set_idTypeSecond("");
    }

    item->fill_data();

    this->SendItem(item);
    this->accept();
}

void
PACSConfigurationFrame
::onDataChanged()
{
    bool status = this->_ui->pacsName->text().toStdString() != "" &&
                  this->_ui->pacsAddress->text().toStdString() != "" &&
                  this->_ui->pacsPort->text().toStdString() != "" &&
                  this->_ui->pacsCalled->text().toStdString() != "" &&
                  this->_ui->pacsCaller->text().toStdString() != "";

    try
    {
        int i = std::stoi(this->_ui->pacsPort->text().toStdString());
        status &= std::to_string(i) == this->_ui->pacsPort->text().toStdString();
    }
    catch (std::invalid_argument &e)
    {
        status = false;
    }

    this->_ui->AcceptButton->setEnabled(status);
}

void
PACSConfigurationFrame
::on_pacsIdType_currentIndexChanged(int index)
{
    bool firstvisible = false;
    bool secondvisible = false;

    if (index == 0)
    {
        // nothing to do
    }
    else if (index == 1)
    {
        firstvisible = true;
    }
    else if (index == 2)
    {
        firstvisible = true;
        secondvisible = true;
    }
    else if (index == 3)
    {// todo
    }
    else if (index == 4)
    {// todo
    }

    this->_ui->firstTitle->setVisible(firstvisible);
    this->_ui->pacsFrist->setVisible(firstvisible);
    this->_ui->secondTitle->setVisible(secondvisible);
    this->_ui->pacsSecond->setVisible(secondvisible);
}

void
PACSConfigurationFrame
::on_TestButton_clicked()
{
    std::string result = "Result: OK";

    try
    {
        odil::Association association;
        association.set_peer_host(this->_ui->pacsAddress->text().toStdString());
        association.set_peer_port(
            std::stoi(this->_ui->pacsPort->text().toStdString()));
        association.update_parameters()
            .set_calling_ae_title(this->_ui->pacsCaller->text().toStdString())
            .set_called_ae_title(this->_ui->pacsCalled->text().toStdString())
            .set_presentation_contexts({
                {
                    1, odil::registry::VerificationSOPClass,
                    { odil::registry::ImplicitVRLittleEndian }, true, true
                }
            });
        association.associate();
        odil::EchoSCU scu(association);
        scu.echo();
        association.release();
    }
    catch (DicomifierException &exc)
    {
        std::stringstream streamresult;
        streamresult << "Result: Fail: " << exc.what();

        result = streamresult.str();
    }
    catch (std::exception &e)
    {
        std::stringstream streamresult;
        streamresult << "Result: Fail: " << e.what();

        result = streamresult.str();
    }

    this->_ui->TestResultTitle->setText(QString(result.c_str()));
}

} // namespace gui

} // namespace dicomifier
