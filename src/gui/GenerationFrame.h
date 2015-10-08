/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c893b98a_2a9d_41b4_bcf7_02699144b4d9
#define _c893b98a_2a9d_41b4_bcf7_02699144b4d9

#include <QProgressDialog>

#include <boost/filesystem.hpp>

#include "BaseFrame.h"
#include "components/GenerationResultItem.h"
#include "components/TreeItem.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class GenerationFrame;
} // namespace Ui

/**
 * @brief The GenerationFrame class
 */
class GenerationFrame : public BaseFrame
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of GenerationFrame
     * @param parent: widget containing the GenerationFrame
     */
    explicit GenerationFrame(QWidget *parent = 0);

    /// Destroy the instance of GenerationFrame
    virtual ~GenerationFrame();

    /// Initialize the instance of GenerationFrame
    virtual void Initialize();

    /// Re-initialize the widget
    virtual void Reset();

    /**
     * @brief Process conversion Bruker -> DICOM
     * @param selectedItems: Selected items (Subject/Study/Series/Reconstruction)
     */
    void RunDicomifier(std::vector<TreeItem*> selectedItems);

    /**
     * @brief Return the process results for each subject
     * @return results
     */
    std::map<std::string, GenerationResultItem> get_Results()
            { return this->_Results; }

    std::string get_selectedFormat_toString() const;

    /**
     * @brief List DICOM files to add into DICOMDIR
     * @param directory: Directory containing DICOM files
     * @param absdirectory: absolute directory
     */
    static std::vector<std::string> getFilesForDicomdir(
            std::string const & directory,
            std::string const & absdirectory);

public slots:
    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences();

signals:
    /// Signal emit to open Preferences Widget and add new PACS
    void CreateNewPACSConfiguration();

protected:
    /// Evaluate the value to set for Enabled property of Next Button
    virtual void modify_nextButton_enabled();

    /// Evaluate the value to set for Enabled property of Previous Button
    virtual void modify_previousButton_enabled();

    void createDicomdirs(std::string const & directory,
                         std::string const & absdirectory,
                         std::string const & dicomdirfile);

    std::string createZipArchives(std::string const & directory,
                                  std::string const & filename);

    void createDicomdirsOrZipFiles(QProgressDialog &progress,
                                   std::map<std::string, std::string> &mapHascodeToSubject);

    /**
     * @brief For each processed item, send the DICOM to selected PACS
     * @param directory: Directory containing DICOM files
     */
    void storeFilesIntoPACS(std::string const & directory);

private slots:
    /// Event triggered by clicking Save checkBox
    void on_saveCheckBox_clicked();

    /// Event triggered by clicking Browse Button
    void on_outputDirBrowseButton_clicked();

    /// Event triggered by modifying output directory LineEdit
    void on_outputDirectory_editingFinished();

    /// Event triggered by modifying output directory LineEdit
    void on_outputDirectory_textEdited(const QString &arg1);

    /// Event triggered by clicking New Button
    void on_CreateButton_clicked();

private:
    /// Save all choices for the next time
    void SavePreferences();

    /// User Interface
    Ui::GenerationFrame * _ui;

    /// Map <subject name, result>
    std::map<std::string, GenerationResultItem> _Results;

};

} // namespace gui

} // namespace dicomifier

#endif // _c893b98a_2a9d_41b4_bcf7_02699144b4d9
