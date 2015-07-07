#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::on_pushButtonChooseDirectory_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
                this,
                "Choose config directory.",
                "~",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
}
