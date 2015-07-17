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
    static QIcon* getIcon(const QString& file);

    ///
    /// \brief Actually create a nodes based on a file path. Used by appendBook.
    /// \param root
    /// \param splitted_path
    /// \param from Create nodes from the position indicated by this parameter.
    ///
    static void create_node(QStandardItem* root, const QStringList& splitted_path, const int from);


public:
    ///
    /// \brief Constructor
    /// \param parent parent object
    ///
    BooksTreeModel(QObject* parent);

    ///
    /// \brief Parse the path to a book and append it to the tree model.
    /// \param path the path to the book
    ///
    void appendBook(const QString& path);

    ///
    /// \brief Parse paths to a list of books and append them to the tree model.
    /// \param paths
    ///
    void appendBooks(const QStringList& paths);
};

#endif // BOOKSTREEMODEL_H
