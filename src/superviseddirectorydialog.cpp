#include "superviseddirectorydialog.h"
#include "ui_superviseddirectorydialog.h"

#include <QFileDialog>
#include <QVector>

SupervisedDirectoryDialog::SupervisedDirectoryDialog(ProgramConfigFile* configFile_,
                                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupervisedDirectoryDialog),
    configFile_(configFile_)
{
    ui->setupUi(this);

    //ui->listWidgetSupervisedDirectory->addItems(configFile_->getSupervisedDirectories());

}

SupervisedDirectoryDialog::~SupervisedDirectoryDialog()
{
    delete ui;
}


void SupervisedDirectoryDialog::on_pushButtonAddDirectory_clicked()
{
//    QString path = QFileDialog::getExistingDirectory(
//                this,
//                "Choose supervised directory.",
//                "~",
//                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
//                );

//    configFile_->addSupervisedDirectory(QDir(path));

//    ui->listWidgetSupervisedDirectory->addItem(path);
}

void SupervisedDirectoryDialog::on_pushButtonRemoveDirectory_clicked()
{
//    for (int ii=0; ii<ui->listWidgetSupervisedDirectory->count(); ii++ )
//        if (ui->listWidgetSupervisedDirectory->item(ii)->isSelected())
//            configFile_->removeSupervisedDirectory(ui->listWidgetSupervisedDirectory->item(ii)->text());

//    qDeleteAll(ui->listWidgetSupervisedDirectory->selectedItems());

}
