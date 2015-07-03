#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include "settingsdialog.h"
#include "programinitializer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Settings, SIGNAL(triggered(bool)), this, SLOT(onSettingsDirectory()));

    ProgramInitializer init;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSettingsDirectory() {
    SettingsDialog diag(this);
    diag.exec();
}
