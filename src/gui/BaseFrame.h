/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _331c28b0_9e09_4517_9709_4714eac0fae8
#define _331c28b0_9e09_4517_9709_4714eac0fae8

#include <QWidget>

namespace dicomifier
{

namespace gui
{

// Const declaration, used by QSettings
QString const CONF_GROUP_INPUT      = "Input";
QString const CONF_GROUP_OUTPUT     = "Output";
QString const CONF_KEY_DIRECTORY    = "directory";
QString const CONF_KEY_FORMAT       = "dicomformat";
QString const CONF_KEY_DICOMDIR     = "dicomdir";
QString const CONF_KEY_ZIP          = "zip";
QString const CONF_KEY_SAVE         = "save";
QString const CONF_KEY_STORE        = "store";

/**
 * @brief The BaseFrame abstract class.
 */
class BaseFrame : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of BaseFrame
     * @param parent: widget containing the BaseFrame
     */
    explicit BaseFrame(QWidget *parent = 0);

    /// Destroy the instance of BaseFrame
    virtual ~BaseFrame();

    /// Initialize the instance of BaseFrame
    virtual void Initialize();

    /// Re-initialize the widget
    virtual void Reset() = 0;

public slots:
    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences() = 0;

protected:
    /**
     * @brief Evaluate the value to set for Enabled property of Next Button
     */
    virtual void modify_nextButton_enabled() = 0;

    /**
     * @brief Evaluate the value to set for Enabled property of Previous Button
     */
    virtual void modify_previousButton_enabled() = 0;

signals:
    /**
     * @brief Signal emit to changed Enabled property of Next Button
     * @param enabled: new value
     */
    void update_nextButton(bool enabled);

    /**
     * @brief Signal emit to changed Enabled property of Previous Button
     * @param enabled: new value
     */
    void update_previousButton(bool enabled);

    /**
     * @brief Signal emit if user cancelled the operation
     */
    void cancelled();

private:

};

} // namespace gui

} // namespace dicomifier

#endif // _331c28b0_9e09_4517_9709_4714eac0fae8
