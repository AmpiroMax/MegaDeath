#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QWidget>

class GameWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
  private:
    sf::Color clearColor;
    sf::View view;

    QTimer timer;

    bool isInited;

  public:
    explicit GameWidget(QWidget *parent = nullptr);

  private:
    virtual QPaintEngine *paintEngine() const override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

  private slots:
    void onTimeout();
};

#endif // GAMEWIDGET_H
