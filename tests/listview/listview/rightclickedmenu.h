#ifndef RIGHTCLICKEDMENU_H
#define RIGHTCLICKEDMENU_H

#include <QMenu>

class RightClickedMenu : public QMenu
{
    Q_OBJECT

public:
    RightClickedMenu(QWidget * parent=0);

    QAction* exec(const QPoint& p);

public slots:
    void handleAction(QAction *);
    void menu1Triggered(bool);
    void menu2Triggered(bool);
};

#endif // RIGHTCLICKEDMENU_H
