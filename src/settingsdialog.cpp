#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonChooseDirectory, SIGNAL(clicked(bool)), this, SLOT(onChooseDirectory()));


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onChooseDirectory() {
    QString path = QFileDialog::getExistingDirectory(
                this,
                "Choose config directory.",
                "~",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
}
