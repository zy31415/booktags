#include "tagsbookswidget.h"
#include "ui_tagsbookswidget.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>

TagsBooksWidget::TagsBooksWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsBooksWidget)
{
    ui->setupUi(this);

    // when different tags are selected
    connect(ui->listWidgetTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));

    // when you try to add a tag:
    connect(this, SIGNAL(tagAdded(QString)), parentWidget(), SLOT(addTag(QString)));

    // when you try to delete a tag:
    connect(this, SIGNAL(selectionDeleted()), parentWidget(), SLOT(deleteSelection()));
}

TagsBooksWidget::~TagsBooksWidget()
{
    delete ui;
}

QString TagsBooksWidget::getSelectedTag() {
    return ui->listWidgetTags->selectedItems()[0]->text();
}


void TagsBooksWidget::updateTagsList(QStringList tags) {
    // disconnect the ralted signal first, otherwise the program will crash.
    disconnect(ui->listWidgetTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));
    ui->listWidgetTags->clear();

    ui->listWidgetTags->addItems(tags);
    connect(ui->listWidgetTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));
    ui->listWidgetTags->setCurrentRow(0);
}

void TagsBooksWidget::setCurrentDirectoryLabel(QString dir) {
    ui->labelCurrentDir->setText("Current Directory: " + dir);
}

// TODO: Use model/view structure to rewrite tags view.
void TagsBooksWidget::onListWidgetTagsItemSelectionChanged()
{
//    ui->listWidgetBooks->clear();

//    foreach (QString file, configCurrentDir_->getFiles(getSelectedTag())) {
//        QFileInfo fileinfo(file); // get file icon
//        QFileIconProvider iconprovider;
//        QIcon icon = iconprovider.icon(fileinfo);

//        if (fileinfo.suffix().toLower() == "pdf")
//            new QListWidgetItem(QIcon(":/icons/pdf.png"), file, ui->listWidgetBooks);
//        else
//            new QListWidgetItem(icon, file, ui->listWidgetBooks);
//    }


//    foreach (QString fileName, configCurrentDir_->getFiles(getSelectedTag())) {
//        QStringList splitFileName =fileName.split("/");

//        addPathIntoTreeWidget(splitFileName);
//    }
}

// TODO: Use model/view structure to rewrite books display.
//          This part can be very complicated.
void TagsBooksWidget::addPathIntoTreeWidget(QStringList splitFileName) {

//    if (splitFileName.size()==1)
//        new QTreeWidgetItem(ui->treeWidgetBooks, splitFileName);
//    else {
//        QTreeWidgetItem* parent = new QTreeWidgetItem(ui->treeWidgetBooks);
//        parent->setText(0, splitFileName[0]);

//        for (int ii=1; ii< splitFileName.size(); ii++) {
//            QString s = splitFileName[ii];
//            QTreeWidgetItem* item = new QTreeWidgetItem();
//            item->setText(0,s);
//            parent->addChild(item);
//            parent = item;
//        }
//    }

}

void TagsBooksWidget::updateBooksListView(QStringList books) {
    ui->listWidgetBooks->clear();

    foreach (QString file, books) {
        QFileInfo fileinfo(file); // get file icon
        QFileIconProvider iconprovider;
        QIcon icon = iconprovider.icon(fileinfo);

        if (fileinfo.suffix().toLower() == "pdf")
            new QListWidgetItem(QIcon(":/icons/pdf.png"), file, ui->listWidgetBooks);
        else
            new QListWidgetItem(icon, file, ui->listWidgetBooks);
    }
}

void TagsBooksWidget::on_pushButtonAddTag_clicked()
{
    bool ok;
    QString tag = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                        tr("New tag name:"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
    if (ok && !tag.isEmpty()) {
        emit tagAdded(tag);
    }
}

void TagsBooksWidget::addTag(QString tag) {
    ui->listWidgetTags->setCurrentItem(
                new QListWidgetItem(tag, ui->listWidgetTags)
                );
}

void TagsBooksWidget::on_pushButtonRemoveTag_clicked()
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


    if (reply == QMessageBox::Yes)
        emit selectionDeleted();
}

void TagsBooksWidget::deleteSelection() {
    delete ui->listWidgetTags->selectedItems()[0];
}
