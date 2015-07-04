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

public slots:
    void onAddDirectory();
    void onRemoveDirectory();
};

#endif // SUPERVISEDDIRECTORYDIALOG_H
