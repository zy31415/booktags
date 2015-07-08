#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "programconfigfile.h"
#include "currentdirectoryconfigurer.h"
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

    CurrentDirectoryConfigurer* configCurrentDir_;

    TagsBooksWidget* tbWidget_;


private slots:
    void on_action_About_triggered();
    void on_actionOpenDirectory_triggered();
    void on_action_Settings_triggered();
    void onCurrentDirectoryChange();
    void on_pushButtonRemoveTag_clicked();
    void onTagsSelectionChanged();

public slots:
    void addTag(const QString& tag);
};

#endif // MAINWINDOW_H
