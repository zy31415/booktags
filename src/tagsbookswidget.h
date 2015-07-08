#ifndef TAGSBOOKSWIDGET_H
#define TAGSBOOKSWIDGET_H

#include <QWidget>

namespace Ui {
class TagsBooksWidget;
}

class TagsBooksWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagsBooksWidget(QWidget *parent = 0);
    ~TagsBooksWidget();

private:
    Ui::TagsBooksWidget *ui;
};

#endif // TAGSBOOKSWIDGET_H
