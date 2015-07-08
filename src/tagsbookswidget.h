#ifndef TAGSBOOKSWIDGET_H
#define TAGSBOOKSWIDGET_H

#include <QWidget>

#include "currentdirectoryconfigurer.h"

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

    void addPathIntoTreeWidget(QStringList splitFileName);


private slots:
    void onListWidgetTagsItemSelectionChanged();

    void on_pushButtonAddTag_clicked();
    void on_pushButtonRemoveTag_clicked();

signals:
    void tagAdded(const QString &);
    void selectionDeleted();
};

#endif // TAGSBOOKSWIDGET_H
