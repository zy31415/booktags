#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QItemSelectionModel>

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

    QStringListModel* list_;
    QItemSelectionModel* selection;

public slots:
    void selectionChanged(
            const QItemSelection& selected,
            const QItemSelection& deselected);
};

#endif // MAINWINDOW_H
