#include "tagsbookswidget.h"
#include "ui_tagsbookswidget.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QStandardItem>
#include <QDebug>
#include <QStringListModel>

#include "filetree.h"

TagsBooksWidget::TagsBooksWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsBooksWidget)
{
    ui->setupUi(this);

    tagsList_ = new TagsListModel(this);    
    ui->listViewTags->setModel(tagsList_);
    tagSelection_ = ui->listViewTags->selectionModel();

    booksTree_ = new BooksTreeModel(this);
    ui->treeViewBooks->setModel(booksTree_);
    bookSelection_ = ui->treeViewBooks->selectionModel();


    // when different tags are selected
    connectTagSelectionSignal();

}

TagsBooksWidget::~TagsBooksWidget()
{
    delete ui;
}

void TagsBooksWidget::connectTagSelectionSignal() {
    connect(tagSelection_,
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this,
            SLOT(changeTagSelection(const QItemSelection&, const QItemSelection&)));

}

///
/// \brief Update the tags list.
/// \param tags
///
/// Do the following things:
///     1. Delete old tags list and create a new tags list;
///     2. Delete the old selection model and connect to the new selection model.
///     3. Update the signal connection of the selection model.
///
void TagsBooksWidget::updateTagsList(QStringList tags) {
    tagsList_->deleteLater();

    tagsList_ = new TagsListModel(this);
    tagsList_->appendTags(tags);
    ui->listViewTags->setModel(tagsList_);

    tagSelection_->deleteLater();
    tagSelection_ = ui->listViewTags->selectionModel();

    // Update the signal connection for the new selection model.
    connectTagSelectionSignal();

    tagSelection_->setCurrentIndex(tagsList_->index(0),QItemSelectionModel::Select);
}

///
/// \brief Update the books tree.
/// \param tags
///
/// Do the following things:
///     1. Delete old books tree and create a new books tree;
///     2. Delete the old selection model and connect to the new selection model.
///     3. Update the signal connection of the selection model.
///
void TagsBooksWidget::updateBooksTree(QStringList books) {
    booksTree_->deleteLater();

    booksTree_ = new BooksTreeModel(this);
    booksTree_->appendBooks(books);
    ui->treeViewBooks->setModel(booksTree_);

    bookSelection_ -> deleteLater();
    bookSelection_ = ui->treeViewBooks->selectionModel();

}

void TagsBooksWidget::setCurrentDirectoryLabel(QString dir) {
    ui->labelCurrentDir->setText("Current Directory: " + dir);
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

void TagsBooksWidget::on_pushButtonRemoveTag_clicked()
{
    QModelIndexList idx;

    if(tagSelection_->hasSelection())
         idx = tagSelection_->selectedIndexes();
    else {
        QMessageBox::warning(this,
                             QString("Deletion error"),
                             QString("Select a tag first."));
        return;
    }

     if (idx.length()!= 1) {
         qDebug() << "Selection error.";
         return;
     }

     QString tag = idx[0].data(Qt::DisplayRole).toString();

     if (tag == QString("all")) {
         QMessageBox::warning(this,
                             QString("Deletion error"),
                             QString("Keep the tag \"all\"."));
         return;
     }

     QString message = QString("Are you sure to delete tag: \"%1\" ?").arg(tag);

     QMessageBox::StandardButton reply = QMessageBox::question(
                 this, "Delete tag", message,
                 QMessageBox::Yes|QMessageBox::No);

     if (reply == QMessageBox::Yes) {
         tagsList_->removeRow(idx.at(0).row());
         emit tagDeleted(tag);
     }
}

void TagsBooksWidget::addOneBookToTag(QString item, QString tag) {
    if (getSelectedTag() == tag)
        booksTree_->appendBook(item);
}

void TagsBooksWidget::changeTagSelection(const QItemSelection& selected,
                                         const QItemSelection& deselected) {

    QString tag = tagSelection_->selectedIndexes()[0].data(Qt::DisplayRole).toString();
    emit tagSelected(tag);
}

QString TagsBooksWidget::getSelectedTag() {
    return tagSelection_->selectedIndexes()[0].data(Qt::DisplayRole).toString();
}

void TagsBooksWidget::appendTag(QString tag) {
    tagsList_->appendTag(tag);
}
