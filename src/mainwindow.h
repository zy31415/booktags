#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QProgressBar>

#include "programconfigfile.h"
#include "directorydatabase.h"
#include "tagsbookswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getCurrentDirectory();


private:
    Ui::MainWindow *ui;
    ProgramConfigFile* configFile_;

    DirectoryDatabase* dirDB_;

    TagsBooksWidget* tbWidget_;
    QProgressBar* qProgressBar_;


private slots:
    void on_action_About_triggered();
    void on_actionOpenDirectory_triggered();
    void on_action_Settings_triggered();
    void onCurrentDirectoryChange();

    void on_action_Scan_direcotry_triggered();

    void onMissingFile(const QString&);

    void onNewBookFound(const QString&);



public slots:

    ///
    /// \brief Add a tag into database;
    /// \param tag tag added
    ///
    void addTag(const QString& tag);

    ///
    /// \brief Delete tag from database;
    ///
    void deleteSelection(const QString& tag);

    void changeStatusBarMessage(QString msg);


    void updateTagsBooksWidget();

    ///
    /// \brief When a new tag selected
    /// \param tag new tag selected
    ///
    /// This slot will read book attached to the new tag from the database
    /// and update the books tree view.
    ///
    void changeTagSelection(const QString& tag);

    ///
    /// \brief This slot is called when the directory scanning started.
    /// \param max
    ///
    void onDirectoryScanStarted(int max);

    ///
    /// \brief This slot is called when the directory scanning finished.
    ///
    void onDirectoryScanFinished();

    ///
    /// \brief This slot is called when the scan status updated.
    /// \param current
    ///
    void onScanStatusUpdate(int current);
};

#endif // MAINWINDOW_H
