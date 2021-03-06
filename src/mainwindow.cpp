#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

// Qt
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFileSystemModel>


// This project
#include "settingsdialog.h"
#include "currentdirectorydialog.h"
#include "scandirectorythread.h"

// TODO - handle matches: click tag to select books, click book to select tags.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dirDB_(0)
{
    ui->setupUi(this);

    configFile_ = new ProgramConfigFile;
    if (!configFile_->ifConfigFileExist())
        configFile_->initConfigFile();

    tbWidget_ = new TagsBooksWidget(this);
    setCentralWidget(tbWidget_);

    connect(tbWidget_, SIGNAL(tagSelected(QString)),
            this, SLOT(changeTagSelection(QString)));
    connect(tbWidget_, SIGNAL(tagDeleted(QString)),
            this, SLOT(deleteSelection(QString)));
    connect(tbWidget_, SIGNAL(tagAdded(QString)),
            this, SLOT(addTag(QString)));

    onCurrentDirectoryChange();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete configFile_;
    delete dirDB_;
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
    if (dirDB_ != 0)
        dirDB_->deleteLater();

    /// Initialize dirDB_, and set up the connection between dirDB_ and the mainwindow.
    dirDB_ = new DirectoryDatabase(this);
    dirDB_->setDir(configFile_->getCurrentDirectory());
    dirDB_->initDatabase();

    /// Initial load of list of tags
    QStringList tags = dirDB_->getTags();

    tbWidget_->updateTagsList(tags);

    // update Main Widget title
    tbWidget_ ->setCurrentDirectoryLabel(getCurrentDirectory());
}

void MainWindow::changeTagSelection(const QString& tag) {
    QStringList files = dirDB_->getBooks(tag);
    tbWidget_->updateBooksTree(files);
}

void MainWindow::addTag(const QString& tag) {
    if (dirDB_->hasTag(tag)) {
        QMessageBox::warning(this,
                             QString("Tag exists."),
                             QString("Tag already exists."));
        return;
    }

    dirDB_->addTag(tag);
    tbWidget_->appendTag(tag);
}

void MainWindow::deleteSelection(const QString& tag) {
    dirDB_->removeTag(tag);
}

void MainWindow::changeStatusBarMessage(QString msg) {
    ui->statusBar->showMessage(msg);
}

void MainWindow::updateTagsBooksWidget() {
    tbWidget_->updateTagsList(dirDB_->getTags());

    // update Main Widget title
    tbWidget_ ->setCurrentDirectoryLabel(getCurrentDirectory());
}


void MainWindow::on_action_Scan_direcotry_triggered()
{
    ScanDirectoryThread* thread_ = new ScanDirectoryThread(
                getCurrentDirectory(),
                this);

    // Handle missing file
    connect(thread_, SIGNAL(missingFile(QString)),
            this, SLOT(onMissingFile(QString)));

    // A new book found.
    connect(thread_, SIGNAL(newBookFound(QString)),
            this, SLOT(onNewBookFound(QString)));

    // when the thread is finished.
    connect(thread_, SIGNAL(finished()),
            thread_, SLOT(deleteLater()));

    // when the thread is started.
    connect(thread_, SIGNAL(started(int)),
            this, SLOT(onDirectoryScanStarted(int)));

    // when the thread is finished.
    connect(thread_, SIGNAL(finished()),
            this, SLOT(onDirectoryScanFinished()));

    // when the thread is progressing and one more file is processed.
    connect(thread_, SIGNAL(updateScanStatus(int)),
            this, SLOT(onScanStatusUpdate(int)));

    thread_->start();

}

void MainWindow::onMissingFile(const QString& path){
    tbWidget_->addOneBookToTag(path,QString("lost"));
    ui->statusBar->showMessage(QString("Missing: ") + path);
}

void MainWindow::onNewBookFound(const QString& path) {
    tbWidget_->addOneBookToTag(path,QString("all"));
    tbWidget_->addOneBookToTag(path,QString("new"));

    ui->statusBar->showMessage(QString("Found: ") + path);
}

void MainWindow::onDirectoryScanStarted(int max) {
    ui->action_Scan_direcotry->setEnabled(false);

    qProgressBar_ = new QProgressBar(ui->statusBar);
    qProgressBar_->setMinimum(0);
    qProgressBar_->setMaximum(max);

    ui->statusBar->addPermanentWidget(qProgressBar_, 0);
}

void MainWindow::onDirectoryScanFinished() {
    ui->statusBar->removeWidget(qProgressBar_);
    qProgressBar_->deleteLater();
    ui->statusBar->showMessage("Directory scanning finished!");

    ui->action_Scan_direcotry->setEnabled(true);

}

void MainWindow::onScanStatusUpdate(int current) {
    qProgressBar_->setValue(current);
}
