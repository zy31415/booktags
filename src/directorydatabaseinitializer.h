/** TODO - implement DirectoryDatabaseInitializer class and file
 * @file This file defines the class DirectoryDatabaseInitializer.
 * This class will use *a parallel thread* to
 *
 * (1) collect all books in the current directory;
 *
 * (2) Add these books into the database if they are not in it.
 *
 * (3) Notify the system the change it has done to the database so that the system can change accordingly.
 *
 * @author Yang Zhang
 *
 */

#ifndef DIRECTORYDATABASEINITIALIZER_H
#define DIRECTORYDATABASEINITIALIZER_H


class DirectoryDatabaseInitializer
{
public:
    DirectoryDatabaseInitializer();
};

#endif // DIRECTORYDATABASEINITIALIZER_H
