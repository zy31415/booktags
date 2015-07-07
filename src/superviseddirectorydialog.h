#ifndef SUPERVISEDDIRECTORYDIALOG_H
#define SUPERVISEDDIRECTORYDIALOG_H

#include <QDialog>
#include "programconfigfile.h"

namespace Ui {
class SupervisedDirectoryDialog;
}

class SupervisedDirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupervisedDirectoryDialog(ProgramConfigFile* configFile_,
                                       QWidget *parent = 0);
    ~SupervisedDirectoryDialog();

private:
    Ui::SupervisedDirectoryDialog *ui;
    ProgramConfigFile* configFile_;

private slots:
    void on_pushButtonAddDirectory_clicked();
    void on_pushButtonRemoveDirectory_clicked();
};

#endif // SUPERVISEDDIRECTORYDIALOG_H
