#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "WorldMap/tilemap.h"

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
    const TileMap *worldMap;

    sf::Color clearColor;
    sf::View view;

    QTimer timer;

    bool isInited;

  public:
    explicit GameWidget(QWidget *parent = nullptr);

    void setWorldMap(const TileMap *map);

  private:
    virtual QPaintEngine *paintEngine() const override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

  private slots:
    void onTimeout();
};

#endif // GAMEWIDGET_H
