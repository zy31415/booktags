#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMutex>

#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Database db;

public slots:
    void updateList();
    void addItem(const QString& item);

private slots:
    void on_action_Scan_directory_triggered();
    void on_action_Scan_directory2_triggered();
};

#endif // MAINWINDOW_H
