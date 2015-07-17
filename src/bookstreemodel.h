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
    static QIcon icon_dir = QIcon(":/icons/directory.png");
    static QIcon icon_pdf = QIcon(":/icons/pdf.png");
    static QIcon icon_epub = QIcon(":/icons/epub.png");
    static QIcon icon_mobi = QIcon(":/icons/mobi.png");
    static QIcon icon_file = QIcon(":/icons/file.png");

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
    ///
    static void add_path(QStandardItem* root, QString path);


public:
    BooksTreeModel(QObject* parent);

    void setBooks(const QStringList& path);
};

#endif // BOOKSTREEMODEL_H
