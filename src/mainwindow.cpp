#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFileSystemModel>

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

    tbWidget_ = new TagsBooksWidget(this);
    setCentralWidget(tbWidget_);

    onCurrentDirectoryChange();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete configFile_;
    delete configCurrentDir_;
}


// getters:
QString MainWindow::getCurrentDirectory() {
    return configFile_ -> getCurrentDirectory();
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
        onCurrentDirectoryChange();
    }
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog diag(this);
    diag.exec();
}

void MainWindow::onCurrentDirectoryChange() {
    if (configCurrentDir_ != 0)
        delete configCurrentDir_;

    configCurrentDir_ = new CurrentDirectoryConfigurer(getCurrentDirectory());

    tbWidget_->updateTagsList(configCurrentDir_->getTags());

    // update Main Widget title
    tbWidget_ ->setCurrentDirectoryLabel(getCurrentDirectory());
}

// TODO - This progress can be very slow. Can you use multi-threading?
void MainWindow::changeTagSelection() {
    QStringList files = configCurrentDir_->getFiles(tbWidget_->getSelectedTag());
    tbWidget_->updateBooksListView(files);
}

void MainWindow::addTag(const QString& tag) {
    // TODO : check if the tag is a valid tag.
    //      if Yes:
    configCurrentDir_->addTag(tag);
    tbWidget_->addTag(tag);
}

void MainWindow::deleteSelection() {
    configCurrentDir_->removeTag(tbWidget_->getSelectedTag());
    tbWidget_->deleteSelection();
}
