#include "mainwindow.h"
#include <QApplication>

#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton quit("Quit");

    MainWindow w;

    quit.setParent(&w);

    QObject obj;
    QWidget widget;


    w.show();





    return a.exec();
}
