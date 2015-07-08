#include "tagsbookswidget.h"
#include "ui_tagsbookswidget.h"

TagsBooksWidget::TagsBooksWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsBooksWidget)
{
    ui->setupUi(this);
}

TagsBooksWidget::~TagsBooksWidget()
{
    delete ui;
}
