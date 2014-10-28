#include "mainframe.h"
#include "ui_mainframe.h"

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::Initialize()
{
    // Remove title bar
    this->setWindowFlags(Qt::CustomizeWindowHint);

    // Window Position and Size
    this->setGeometry(0, 0, 1024, 768);

    // Connect Signals <-> Slots
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}
