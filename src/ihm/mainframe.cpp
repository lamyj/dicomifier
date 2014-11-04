#include "SubjectsFrame.h"
#include "mainframe.h"
#include "ui_mainframe.h"

#include <QGridLayout>

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    this->ui->actionQuit->setShortcuts(QKeySequence::Quit);
    this->ui->actionQuit->setStatusTip(tr("Close the application"));
    connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    this->ui->actionNew->setShortcuts(QKeySequence::New);
    this->ui->actionNew->setStatusTip(tr("New process"));
    //connect(this->ui->actionNew, SIGNAL(triggered()), this, SLOT()); TODO

    this->ui->actionPreferences->setShortcuts(QKeySequence::Preferences);
    this->ui->actionPreferences->setStatusTip(tr("Modify Dicomifier Preferences"));
    //connect(this->ui->actionPreferences, SIGNAL(triggered()), this, SLOT()); TODO
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::Initialize()
{
    // Window Position and Size
    this->setGeometry(0, 0, 1024, 768);
}
