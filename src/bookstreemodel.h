#ifndef BOOKSTREEMODEL_H
#define BOOKSTREEMODEL_H

#include <QObject>
#include <QStandardItemModel>


class BooksTreeModel : public QStandardItemModel
{
    Q_OBJECT

private:
    ///
    /// \brief Icons for different file types.
    /// These icons are defined as static member to avoid memory leak and large memory use for icons.
    ///
    static QIcon icon_dir, icon_pdf, icon_epub, icon_mobi, icon_file;

    ///
    /// \brief Return an icon based on the format of an input file.
    /// \param input file path
    /// \return A pointer to the icon.
    ///
    static QIcon* getIcon(QString file);

    ///
    /// \brief Actually create a file path nodes.
    /// \param root
    /// \param splitted_path
    /// \param from
    ///
    static void create_node(QStandardItem* root, QStringList splitted_path, int from);

    ///
    /// \brief Add an QStandardItem to the model.
    /// \param root QStandardItem
    /// \param path
    ///
    void add_path(QString path);


public:
    BooksTreeModel(QObject* parent);

    void setBooks(const QStringList& path);
};

#endif // BOOKSTREEMODEL_H
