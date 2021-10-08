#include "keyboardhandler.h"
#include <QKeyEvent>

KeyBoardHandler::KeyBoardHandler(QWidget *parent) : QWidget(parent)
{
    // Строгая фокусировка, позволяющая отлавливать события клавиатуры
    setFocusPolicy(Qt::StrongFocus);
}

void KeyBoardHandler::keyPressEvent(QKeyEvent *event)
{
    int key;
    key = event->key();

    if (key == Qt::Key_A)
        emit moveKeyPressed(key);
    if (key == Qt::Key_W)
        emit moveKeyPressed(key);
    if (key == Qt::Key_S)
        emit moveKeyPressed(key);
    if (key == Qt::Key_D)
        emit moveKeyPressed(key);

    switch (key)
    {
        case Qt::Key_Escape:
        case Qt::Key_Q:
        {
            emit quitKeyPressed();
            break;
        }
        case Qt::Key_Z:
        case Qt::Key_X:
        {
            emit zoomKeyPressed(key);
            break;
        }
        default:
        {
        }
    }
}
