#include "SubjectsFrame.h"
#include "mainframe.h"
#include "ui_mainframe.h"

#include <QGridLayout>

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    /*QGridLayout m_MainLayout;
    m_MainLayout.setMargin(0);  // No space between window's element and the border
    m_MainLayout.setSpacing(0); // No space between window's element
    setLayout(&m_MainLayout);*/
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
