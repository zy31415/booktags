#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QProgressBar>

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
    QProgressBar* qProgressBar_;


private slots:
    void on_action_About_triggered();
    void on_actionOpenDirectory_triggered();
    void on_action_Settings_triggered();
    void onCurrentDirectoryChange();
    void changeTagSelection();

public slots:
    void addTag(const QString& tag);
    void deleteSelection();
    void changeStatusBarMessage(QString msg);
    void updateTagsBooksWidget();
    void setStatusBarForInitialLoading(int max);
    void updateStatusBarForInitialLoading(int current, QString file);
};

#endif // MAINWINDOW_H
