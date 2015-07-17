/** \file tagsbookswidget.h
 * Define a widget TagsBooksWidget which contains a tags list and a books list.
 *
 * \author Yang Zhang
 */

#ifndef TAGSBOOKSWIDGET_H
#define TAGSBOOKSWIDGET_H


#include <QWidget>
#include <QItemSelectionModel>

#include "currentdirectoryconfigurer.h"
#include "tagslistmodel.h"
#include "bookstreemodel.h"

namespace Ui {
class TagsBooksWidget;
}

class TagsBooksWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagsBooksWidget(QWidget *parent = 0);
    ~TagsBooksWidget();

    ////
    /// \brief Set the label to indicate current directory.
    /// \param dir current directory.
    ///
    void setCurrentDirectoryLabel(QString dir);

    ///
    /// \brief Update tags list according the input.
    /// \param tags tags list
    ///
    /// The old tags list will be deleted if there is any,
    /// and new tags list will be generated.
    /// Current selection will be set to the first tag, and thus
    /// tagSelected() signal will be emitted.
    ///
    void updateTagsList(QStringList tags);

    ///
    /// \brief This method updates the books view according to the input.
    /// \param books book paths used to update the book view.
    ///
    /// The old books tree will be deleted and a new books tree will be generated.
    /// No selection change signal will be emitted.
    ///
    void updateBooksTree(QStringList books);

    void appendTag(QString tag);


private:
    Ui::TagsBooksWidget *ui;

    TagsListModel *tagsList_;
    QItemSelectionModel* tagSelection_;

    BooksTreeModel *booksTree_;
    QItemSelectionModel* bookSelection_;

    ///
    /// \brief This function connection selectionChanged signal of tags list to proper handeling function.
    ///
    void connectTagSelectionSignal();


private slots:

    ///
    /// \brief When add a tag button is clicked
    /// When Add Tag button is pushed, a dialog of adding tag will be shown to
    /// obtain the new tag information. When the adding is confirmed, the newly
    /// added tag will be append to the tags list model and a signal: tagAdded(tag)
    /// will be emitted.
    ///
    void on_pushButtonAddTag_clicked();

    ///
    /// \brief When delete a tag button is clicked
    ///
    void on_pushButtonRemoveTag_clicked();

    ///
    /// \brief When tag selection is changed.
    ///
    void changeTagSelection(const QItemSelection&, const QItemSelection&);

public slots:
    void addOneBookToTag(QString item, QString tag);

signals:

    ///
    /// \brief This signal will be emitted when a tag is succesfully added to the tags list.
    /// \param tag tag that is added
    ///
    /// This signal can be used to notify the database to change accordingly
    ///
    void tagAdded(const QString &);

    ///
    /// \brief This signal will be emitted when a tag is successfully deleted.
    /// \param tag tag that is deleted.
    ///
    void tagDeleted(const QString &);

    ///
    /// \brief This signal will be emitted when a new tag is selected.
    /// \param tag tag that is selected.
    ///
    void tagSelected(const QString& tag);
};

#endif // TAGSBOOKSWIDGET_H
