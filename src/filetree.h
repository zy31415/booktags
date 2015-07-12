/// \file filetree.h
/// This header defines functions that are used to create a tree Model for paths.
/// \author Yang Zhang


#ifndef FILETREE_H
#define FILETREE_H

#include <QIcon>
#include <QString>
#include <QStringList>
#include <QStandardItem>

QIcon* getIcon(QString file);

void create_node(QStandardItem* root, QStringList splitted_path, int from);

void add_path(QStandardItem* root, QString path);

#endif
