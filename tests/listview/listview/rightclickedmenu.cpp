#include "rightclickedmenu.h"

#include <QDebug>

RightClickedMenu::RightClickedMenu(QWidget* parent) : QMenu(parent)
{
    connect(addAction("Menu Item 1"),SIGNAL(triggered(bool)),
            this, SLOT(menu1Triggered(bool)));

    connect(addAction("Menu Item 2"), SIGNAL(triggered(bool)),
            this, SLOT(menu2Triggered(bool)));
    addAction("Menu Item 3");
    addAction("Menu Item 4");

    connect(this, SIGNAL(triggered(QAction*)),
            this, SLOT(handleAction(QAction *)));

}

QAction* RightClickedMenu::exec(const QPoint& p) {
    return QMenu::exec(p);
}

void RightClickedMenu::handleAction(QAction * action) {
    qDebug()<<action->text();
}

void RightClickedMenu::menu1Triggered(bool p) {
    qDebug()<<"menu 1 triggered.";
}

void RightClickedMenu::menu2Triggered(bool p) {
    qDebug()<<"menu 2 triggered.";
}
