#include "mousehandler.h"
#include <QMouseEvent>

MouseHandler::MouseHandler(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void MouseHandler::mousePressEvent(QMouseEvent *event)
{
    printf("Emited \n");
    emit trackMouse(event->pos().x(), event->pos().y());
}
