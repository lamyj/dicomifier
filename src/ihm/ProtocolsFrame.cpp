#include "ProtocolsFrame.h"
#include "ui_ProtocolsFrame.h"
#include <iostream>
namespace dicomifier
{

namespace ihm
{

ProtocolsFrame
::ProtocolsFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::ProtocolsFrame)
{
    this->_ui->setupUi(this);

    this->_treeView = new ProtocolsTreeView(this->_ui->widget);
}

ProtocolsFrame
::~ProtocolsFrame()
{
    delete this->_ui;
}

void
ProtocolsFrame
::Initialize()
{
    this->modify_previousButton_enabled();
    this->modify_nextButton_enabled();

    this->show();
}

void ProtocolsFrame::Reset()
{

}

void
ProtocolsFrame
::modify_nextButton_enabled()
{
    // TODO
    emit this->update_nextButton(false);
}

void
ProtocolsFrame
::modify_previousButton_enabled()
{
    // always true
    emit this->update_previousButton(true);
}

void ProtocolsFrame::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        this->_treeView->resize(this->_ui->widget->size());
    }

    QWidget::paintEvent(event);
}

} // namespace ihm

} // namespace dicomifier
