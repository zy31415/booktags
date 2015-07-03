#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonChooseDirectory, SIGNAL(clicked(bool)), this, onChooseDirectory());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

SettingsDialog::onChooseDirectory() {

}
