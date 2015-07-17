/** \file tagsbookswidget.h
 * Define a widget TagsBooksWidget which contains a tags list and a books list.
 *
 * \author Yang Zhang
 */

#ifndef TAGSBOOKSWIDGET_H
#define TAGSBOOKSWIDGET_H


#include <QWidget>

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

    void updateTagsList(QStringList tags);
    void setCurrentDirectoryLabel(QString dir);
    QString getSelectedTag();

    void updateBooksListView(QStringList books);

    void addTag(QString tag);
    void deleteSelection();

private:
    Ui::TagsBooksWidget *ui;

    TagsListModel *tagsList_;
    BooksTreeModel *booksTree_;

private slots:

    void on_pushButtonAddTag_clicked();
    void on_pushButtonRemoveTag_clicked();

public slots:
    void addOneBookToTag(QString item, QString tag);

signals:
    void tagAdded(const QString &);
    void selectionDeleted();
};

#endif // TAGSBOOKSWIDGET_H
