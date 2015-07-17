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


    // when different tags are selected
    connect(ui->listViewTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));

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
    QModelIndexList index = ui->listViewTags->selectionModel()->selectedIndexes();
    return ui->listViewTags->model()->data(index[0], Qt::DisplayRole).toString();
}


// TODO - Change to Model/View structure. Define your own Model.
void TagsBooksWidget::updateTagsList(QStringList tags) {
    // disconnect the ralted signal first, otherwise the program will crash.
    disconnect(ui->listViewTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));

    QStringListModel* tags_ = new QStringListModel(tags, this);

    ui->listViewTags->setModel(tags_);

//    ui->listWidgetTags->clear();

//    ui->listWidgetTags->addItems(tags);
    connect(ui->listViewTags, SIGNAL(itemSelectionChanged()), parentWidget(), SLOT(changeTagSelection()));
    //ui->listViewTags->setCurrentRow(0);
}

void TagsBooksWidget::setCurrentDirectoryLabel(QString dir) {
    ui->labelCurrentDir->setText("Current Directory: " + dir);
}

///
/// \brief This method updates the books view according to the input.
/// \param books book paths used to update the book view.
///
/// This function is called by the MainWindow.
///
///  TODO - Simplify the file viewing window.
void TagsBooksWidget::updateBooksListView(QStringList books) {

    // TODO - define your own model here for tree display of files. But you want to test your model first.
    QStandardItemModel* model_ = new QStandardItemModel(this);
    QStandardItem *parentItem = model_->invisibleRootItem();

    foreach (QString file, books)
        add_path(parentItem, file);

    ui->treeViewBooks->setModel(model_);
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
//    ui->listWidgetTags->setCurrentItem(
//                new QListWidgetItem(tag, ui->listWidgetTags)
//                );
}

void TagsBooksWidget::on_pushButtonRemoveTag_clicked()
{
//    QListWidgetItem* item_ = ui->listWidgetTags->selectedItems()[0];

//    if (item_->text().trimmed() == QString("all")) {
//        QMessageBox::warning(this,
//                            QString("Deletion error"),
//                            QString("Keep the tag \"all\"."));
//        return;
//    }

//    QString message = QString("Are you sure to delete tag: \"%1\" ?").arg(item_->text());

//    QMessageBox::StandardButton reply = QMessageBox::question(
//                this, "Delete tag", message,
//                QMessageBox::Yes|QMessageBox::No);


//    if (reply == QMessageBox::Yes)
//        emit selectionDeleted();
}

///
/// \brief Delete selected tag.
///
void TagsBooksWidget::deleteSelection() {
//    delete ui->listWidgetTags->selectedItems()[0];
}

///
/// \brief One book item will be shown under the indicated tag.
/// \param item book name
/// \param tag tag name
///
void TagsBooksWidget::addOneBookToTag(QString item, QString tag) {
//    if (ui->listWidgetTags->selectedItems()[0]->text() == tag)
//        ui->listWidgetBooks->addItem(item);
}
