/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PACSConfigurationFrame.h"
#include "ui_PACSConfigurationFrame.h"

#include <iostream>
#include <stdexcept>

#include "dcmtk/config/osconfig.h" /* make sure OS specific configuration is included first */
#include "dcmtk/dcmnet/assoc.h"
#include "dcmtk/dcmnet/dimse.h"

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
        item->set_identityType((UserIdentityType)this->_ui->pacsIdType->currentIndex());
        item->set_idTypeFirst(this->_ui->pacsFrist->text().toStdString());
        item->set_idTypeSecond(this->_ui->pacsSecond->text().toStdString());
    }
    else
    {
        item->set_identityType(UserIdentityType::None);
        item->set_idTypeFirst("");
        item->set_idTypeSecond("");
    }

    item->fill_data();

    emit this->SendItem(item);
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
    std::string result = "";

    try
    {
        T_ASC_Network * networkSCU;
        OFCondition condition = ASC_initializeNetwork(NET_REQUESTOR,
                                                      0, 30, &networkSCU);

        T_ASC_Parameters * params;
        if (condition.good())
        {
            condition = ASC_createAssociationParameters(&params, ASC_MAXIMUMPDUSIZE);
        }

        if (condition.good())
        {
            condition = ASC_setAPTitles(params,
                                        this->_ui->pacsCaller->text().toStdString().c_str(),
                                        this->_ui->pacsCalled->text().toStdString().c_str(),
                                        NULL);
        }

        if (condition.good())
        {
            std::stringstream addressport;
            addressport << this->_ui->pacsAddress->text().toStdString() << ":"
                        << this->_ui->pacsPort->text().toStdString();

            condition = ASC_setPresentationAddresses(params, "localhost",
                                                     addressport.str().c_str());
        }

        if (condition.good())
        {
            typedef std::pair<std::string, std::vector<std::string> > PresentationContext;
            std::vector<PresentationContext> presentation_contexts;
            std::vector<std::string> tempvect = { UID_LittleEndianImplicitTransferSyntax };
            presentation_contexts.push_back(std::make_pair(UID_VerificationSOPClass,
                                                           tempvect));
            presentation_contexts.push_back(std::make_pair(UID_MRImageStorage,
                                                           tempvect));
            presentation_contexts.push_back(std::make_pair(UID_EnhancedMRImageStorage,
                                                           tempvect));

            unsigned int context_id = 1;
            for(auto const & context: presentation_contexts)
            {
                char const ** transfer_syntaxes = new char const *[context.second.size()];
                for(std::size_t i = 0; i < context.second.size(); ++i)
                {
                    transfer_syntaxes[i] = context.second[i].c_str();
                }

                if (condition.good())
                {
                    condition = ASC_addPresentationContext(params, context_id,
                                                           context.first.c_str(),
                                                           transfer_syntaxes,
                                                           context.second.size());
                }

                context_id += 2;
            }
        }

        T_ASC_Association * association;
        if (condition.good())
        {
            condition = ASC_requestAssociation(networkSCU, params, &association);
        }

        if (condition.good())
        {
            DIC_US const message_id = association->nextMsgID++;
            DIC_US status;
            DcmDataset *detail = NULL;
            condition = DIMSE_echoUser(association, message_id, DIMSE_BLOCKING, 30,
                                       &status, &detail);
        }

        if (condition.good())
        {
            condition = ASC_dropAssociation(association);
        }

        if (condition.good())
        {
            condition = ASC_destroyAssociation(&association);
        }

        if (condition.good())
        {
            condition = ASC_dropNetwork(&networkSCU);
        }

        std::stringstream streamresult;
        streamresult << "Result: ";
        if (condition.good())
        {
            streamresult << "OK";
        }
        else
        {
            streamresult << "Fail: " << condition.text();
        }

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
