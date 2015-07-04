#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDir>
#include <QDebug>

#include "filescanner.h"
#include "settingsdialog.h"
#include "directoryinitializer.h"
#include "superviseddirectorydialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Settings, SIGNAL(triggered(bool)), this, SLOT(onSettingsDirectory()));
    connect(ui->actionAddDirectory, SIGNAL(triggered(bool)), this, SLOT(onAddDirectory()));

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

void MainWindow::onSettingsDirectory() {
    SettingsDialog diag(this);
    diag.exec();
}

void MainWindow::onAddDirectory() {
    SupervisedDirectoryDialog diag(configFile_, this);
    diag.exec();
}
