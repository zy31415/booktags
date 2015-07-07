#ifndef CURRENTDIRECTORYDIALOG_H
#define CURRENTDIRECTORYDIALOG_H

#include <QDialog>

namespace Ui {
class CurrentDirectoryDialog;
}

class CurrentDirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CurrentDirectoryDialog(QString currentDirectory,
                                       QWidget *parent = 0);
    ~CurrentDirectoryDialog();

    QString getCurrentDirectory();

private:
    Ui::CurrentDirectoryDialog *ui;
    QString currentDirectory;

private slots:
    void on_pushButtonChooseDirectory_clicked();
};

#endif // CURRENTDIRECTORYDIALOG_H
