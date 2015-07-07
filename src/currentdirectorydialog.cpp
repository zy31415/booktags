#include "currentdirectorydialog.h"
#include "ui_currentdirectorydialog.h"

#include <QFileDialog>
#include <QVector>

CurrentDirectoryDialog::CurrentDirectoryDialog(QString currentDirectory,
                                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurrentDirectoryDialog),
    currentDirectory(currentDirectory)
{
    ui->setupUi(this);

    ui->lineEdit->setText(currentDirectory);

}

CurrentDirectoryDialog::~CurrentDirectoryDialog()
{
    delete ui;
}


QString CurrentDirectoryDialog::getCurrentDirectory() {
    return ui->lineEdit->text().trimmed();
}



void CurrentDirectoryDialog::on_pushButtonChooseDirectory_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
                this,
                "Choose a directory.",
                ui->lineEdit->text(),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    if (path != QString())
        ui->lineEdit->setText(path);
}
