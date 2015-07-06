#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

#include "filescanner.h"
#include "settingsdialog.h"
#include "directoryinitializer.h"
#include "superviseddirectorydialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configFile_ = new ProgramConfigFile;
    if (!configFile_->ifConfigFileExist())
        configFile_->initConfigFile();

    QString file = configFile_ -> getSupervisedDirectory();
    qDebug() << file;


}

MainWindow::~MainWindow()
{
    delete ui;
    delete configFile_;
}

void MainWindow::on_action_About_triggered()
{
    QString title("About booktags");
    QString text("<h1>BookTags</h1>");
    QMessageBox::about(this, title, text);
}

void MainWindow::on_actionOpenDirectory_triggered()
{
    SupervisedDirectoryDialog diag(configFile_, this);
    diag.exec();
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog diag(this);
    diag.exec();
}
