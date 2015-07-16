#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelection>

#include "stringlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_action_Add_triggered();

    void on_action_Selected_triggered();

    void handleSelectionChanged(const QItemSelection& selection,
                                const QItemSelection& deselected);

    void handleCurrentChanged(const QModelIndex&,
                              const QModelIndex&);

    void handleDoubleClicked(const QModelIndex&);

    void userListMenuRequested(const QPoint &);

private:
    Ui::MainWindow *ui;

    StringListModel* listModel;
};

#endif // MAINWINDOW_H
