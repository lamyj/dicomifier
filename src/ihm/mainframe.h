/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b6541ba8_6b89_4c08_95f1_69a3f8235a28
#define _b6541ba8_6b89_4c08_95f1_69a3f8235a28

#include <QMainWindow>

namespace dicomifier
{

namespace ihm
{

namespace Ui
{
class MainFrame;
} // namespace Ui

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void Initialize();

private:
    Ui::MainFrame * _ui;

};

} // namespace ihm

} // namespace dicomifier

#endif // _b6541ba8_6b89_4c08_95f1_69a3f8235a28
