#include "sfmlwidget.h"

void SFMLWidget::onClose()
{
    QWidget::close();
}

SFMLWidget::SFMLWidget(QWidget *parent) : QWidget(parent)
{
    this->showFullScreen();
    sfmlCanvasWidget = new Canvas(this);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(sfmlCanvasWidget, 0, 0);

    setAttribute(Qt::WA_QuitOnClose);

    connect(&*sfmlCanvasWidget, &Canvas::closeWindow, this, &SFMLWidget::onClose);
}

SFMLWidget::~SFMLWidget()
{
}
