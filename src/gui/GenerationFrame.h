/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c893b98a_2a9d_41b4_bcf7_02699144b4d9
#define _c893b98a_2a9d_41b4_bcf7_02699144b4d9

#include "BaseFrame.h"
#include "components/TreeItem.h"
#include "dicom/DicomDirGenerator.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class GenerationFrame;
}

class GenerationFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit GenerationFrame(QWidget *parent = 0);
    virtual ~GenerationFrame();

    virtual void Reset();

    void RunDicomifier(std::vector<TreeItem*> selectedItems);

public slots:
    virtual void onUpdate_Preferences();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void insertFilesForDicomdir(std::string const & directory, DicomDirGenerator* dcmdirgenerator);

private slots:
    void on_saveCheckBox_clicked();

    void on_outputDirBrowseButton_clicked();

    void on_outputDirectory_editingFinished();

    void on_outputDirectory_textEdited(const QString &arg1);

private:
    Ui::GenerationFrame * _ui;

};

} // namespace gui

} // namespace dicomifier

#endif // _c893b98a_2a9d_41b4_bcf7_02699144b4d9
