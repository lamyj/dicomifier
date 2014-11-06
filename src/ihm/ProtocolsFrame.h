#ifndef PROTOCOLSFRAME_H
#define PROTOCOLSFRAME_H

#include "BaseFrame.h"
#include "components/ProtocolsTreeView.h"

namespace dicomifier
{

namespace ihm
{

namespace Ui {
class ProtocolsFrame;
}

class ProtocolsFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit ProtocolsFrame(QWidget *parent = 0);
    virtual ~ProtocolsFrame();

    virtual void Initialize();

    virtual void Reset();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void paintEvent(QPaintEvent *event);

private:
    Ui::ProtocolsFrame * _ui;

    ProtocolsTreeView * _treeView;

};

} // namespace ihm

} // namespace dicomifier

#endif // PROTOCOLSFRAME_H
