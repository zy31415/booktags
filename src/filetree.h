/**
 *  \file filetree.h
 * This header defines functions that turn a file path to a tree model.
 *
 * \author Yang Zhang
 *
 */


#ifndef FILETREE_H
#define FILETREE_H

#include <QIcon>
#include <QString>
#include <QStringList>
#include <QStandardItem>



void create_node(QStandardItem* root, QStringList splitted_path, int from);



#endif
