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
    dirDB_ = new DirectoryDatabase(
                getCurrentDirectory(),
                this);

    connect(dirDB_, SIGNAL(initialDatabaseLoadStarted(int)),
            this, SLOT(setStatusBarForInitialLoading(int)));

    connect(dirDB_, SIGNAL(initialDatabaseLoadFinished()),
            this, SLOT(finishInitialDatabaseLoad()));

    connect(dirDB_, SIGNAL(initialDatabaseLoadOneBookAdded(int,QString)),
            this, SLOT(updateStatusBarForInitialLoading(int, QString)));


    /// Initial load of list of tags
    QStringList tags = dirDB_->getTags();

    tbWidget_->updateTagsList(tags);

    // update Main Widget title
    tbWidget_ ->setCurrentDirectoryLabel(getCurrentDirectory());
}

void MainWindow::changeTagSelection(const QString& tag) {
    QStringList files = dirDB_->getFiles(tag);
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


void MainWindow::setStatusBarForInitialLoading(int max) {
    qProgressBar_ = new QProgressBar(ui->statusBar);
    qProgressBar_->setMinimum(0);
    qProgressBar_->setMaximum(max);

    ui->statusBar->addPermanentWidget(qProgressBar_, 0);

}

void MainWindow::updateStatusBarForInitialLoading(int current, QString file) {
    qProgressBar_->setValue(current);
    ui->statusBar->showMessage(file);

    tbWidget_->addOneBookToTag(file, QString("all"));
}

void MainWindow::finishInitialDatabaseLoad(){
    ui->statusBar->removeWidget(qProgressBar_);
    qProgressBar_->deleteLater();
    ui->statusBar->showMessage("Initial load finished!");
}
