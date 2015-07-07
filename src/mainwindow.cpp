#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

#include "filescanner.h"
#include "settingsdialog.h"
#include "directoryinitializer.h"
#include "currentdirectorydialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    configCurrentDir_(0)
{
    ui->setupUi(this);

    configFile_ = new ProgramConfigFile;
    if (!configFile_->ifConfigFileExist())
        configFile_->initConfigFile();

    onCurrentDirectoryChange();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete configFile_;
    delete configCurrentDir_;
}

void MainWindow::on_action_About_triggered()
{
    QString title("About booktags");
    QString text("<h1>BookTags</h1>");
    QMessageBox::about(this, title, text);
}

void MainWindow::on_actionOpenDirectory_triggered()
{
    CurrentDirectoryDialog diag(configFile_->getCurrentDirectory(), this);
    if (diag.exec() == QDialog::Accepted) {
        configFile_->setCurrentDirectory(diag.getCurrentDirectory());

        //
        onCurrentDirectoryChange();
    }
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog diag(this);
    diag.exec();
}


void MainWindow::onCurrentDirectoryChange() {
    // update Main Widget title
    ui->groupBox->setTitle("Directory: " + getCurrentDirectory());


    if (configCurrentDir_ != 0)
        delete configCurrentDir_;

    configCurrentDir_ = new CurrentDirectoryConfigurer(getCurrentDirectory());
}

QString MainWindow::getCurrentDirectory() {
    return configFile_ -> getCurrentDirectory();
}
