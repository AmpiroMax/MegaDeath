#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include <QWidget>

class MouseHandler : public QWidget
{
    Q_OBJECT
  public:
    explicit MouseHandler(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *) override;
    // virtual void mouseMoveEvent(QMouseEvent *) override;

  signals:
    void trackMouse(int x, int y);
};

#endif // MOUSEHANDLER_H
