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


// TODO: Rearrange the initialization logic.
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

    ui->listWidgetTags->addItems(configCurrentDir_->getTags());
    ui->listWidgetTags->setCurrentRow(0);
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

QString MainWindow::getSelectedTag() {
    return ui->listWidgetTags->selectedItems()[0]->text();
}


// TODO: Use model/view structure to rewrite tags view.
void MainWindow::on_listWidgetTags_itemSelectionChanged()
{
    ui->listWidgetBooks->clear();

    foreach (QString file, configCurrentDir_->getFiles(getSelectedTag())) {
        QFileInfo fileinfo(file); // get file icon
        QFileIconProvider iconprovider;
        QIcon icon = iconprovider.icon(fileinfo);

        if (fileinfo.suffix().toLower() == "pdf")
            new QListWidgetItem(QIcon(":/icons/pdf.png"), file, ui->listWidgetBooks);
        else
            new QListWidgetItem(icon, file, ui->listWidgetBooks);
    }


    foreach (QString fileName, configCurrentDir_->getFiles(getSelectedTag())) {
        QStringList splitFileName =fileName.split("/");

        addPathIntoTreeWidget(splitFileName);

    }
}

// TODO: Use model/view structure to rewrite books display.
//          This part can be very complicated.
void MainWindow::addPathIntoTreeWidget(QStringList splitFileName) {

    if (splitFileName.size()==1)
        new QTreeWidgetItem(ui->treeWidgetBooks, splitFileName);
    else {
        QTreeWidgetItem* parent = new QTreeWidgetItem(ui->treeWidgetBooks);
        parent->setText(0, splitFileName[0]);

        for (int ii=1; ii< splitFileName.size(); ii++) {
            QString s = splitFileName[ii];
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0,s);
            parent->addChild(item);
            parent = item;
        }
    }

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

void MainWindow::on_pushButtonAddTag_clicked()
{
    bool ok;
    QString tag = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("New tag name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !tag.isEmpty()) {
        configCurrentDir_->addTag(tag);
        ui->listWidgetTags->setCurrentItem(
                    new QListWidgetItem(tag, ui->listWidgetTags)
                    );
    }
}

void MainWindow::on_pushButtonRemoveTag_clicked()
{
    QListWidgetItem* item_ = ui->listWidgetTags->selectedItems()[0];

    if (item_->text().trimmed() == QString("all")) {
        QMessageBox::warning(this,
                            QString("Deletion error"),
                            QString("Keep the tag \"all\"."));
        return;
    }


    QString message = QString("Are you sure to delete tag: \"%1\" ?").arg(item_->text());

    QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Delete tag", message,
                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        configCurrentDir_->removeTag(item_->text().trimmed());
        delete item_;
    }


}
