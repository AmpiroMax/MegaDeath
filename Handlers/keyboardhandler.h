#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QWidget>

class KeyBoardHandler : public QWidget
{
    Q_OBJECT
  private:
    virtual void keyPressEvent(QKeyEvent *) override;

  public:
    explicit KeyBoardHandler(QWidget *parent = nullptr);

  signals:
    void quitKeyPressed();
    void moveKeyPressed(int key);
    void zoomKeyPressed(int key);
};

#endif // KEYBOARDHANDLER_H
