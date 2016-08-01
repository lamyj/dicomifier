/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c893b98a_2a9d_41b4_bcf7_02699144b4d9
#define _c893b98a_2a9d_41b4_bcf7_02699144b4d9

#include <map>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include <QtCore>
#include <QtGui>

#include "BaseFrame.h"
#include "components/GenerationResultItem.h"
#include "components/TreeItem.h"

namespace dicomifier
{

namespace gui
{

namespace Ui
{

class GenerationFrame;

}

/// @brief Widget converting Bruker data and reporting on the conversion.
class GenerationFrame: public BaseFrame
{
    Q_OBJECT

public:
    /// @brief Constructor
    explicit GenerationFrame(QWidget *parent = 0);

    /// @brief Destructor.
    virtual ~GenerationFrame();

    /// @brief Initialize the instance of GenerationFrame
    virtual void Initialize();

    /// @brief Re-initialize the widget
    virtual void Reset();

    /// @brief Convert selected reconstructions from Bruker to DICOM.
    void generate(std::vector<TreeItem*> const & selected_items);

    /// @brief Return the process results for each subject.
    std::map<std::string, GenerationResultItem> get_results() const;

public slots:
    /// @brief Event triggered when preferences are modified.
    virtual void onUpdate_Preferences();

signals:
    /// @brief Signal emitted to open Preferences widget and add new PACS entry.
    void CreateNewPACSConfiguration();

private:
    typedef boost::filesystem::path Path;

    /// @brief User interface.
    Ui::GenerationFrame * _ui;

    /// @brief Map a subject to its conversion results.
    std::map<std::string, GenerationResultItem> _results;

    /// Evaluate the value to set for Enabled property of Next Button
    virtual void modify_nextButton_enabled();

    /// Evaluate the value to set for Enabled property of Previous Button
    virtual void modify_previousButton_enabled();

    /// @brief Create a DICOMDIR for a set of files belonging to a single subject.
    void _create_dicomdir(std::vector<Path> const & files) const;

    /// @brief Create a ZIP archive for a set of files belonging to a single subject.
    std::string _create_zip_archive(
        std::string const & subject, std::vector<Path> const & files,
        bool has_dicomdir) const;

    /// @brief Create extra files (DICOMDIR, ZIP archive, etc.).
    void _create_extra_files(
        QProgressDialog & progress,
        std::map<std::string, std::vector<Path>> const & subject_files);

    /**
     * @brief For each processed item, send the DICOM to selected PACS
     * @param directory: Directory containing DICOM files
     */
    void _store_files_in_pacs(std::string const & directory);

    /// @brief Save all preferences.
    void _save_preferences();

private slots:
    void on_save_check_box_clicked();

    void on_output_directory_button_clicked();

    void on_output_directory_text_editingFinished();

    void on_output_directory_text_textEdited(QString const &);

    void on_pacs_button_clicked();

};

} // namespace gui

} // namespace dicomifier

#endif // _c893b98a_2a9d_41b4_bcf7_02699144b4d9
