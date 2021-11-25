#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "Interfaces/IUnit.h"
#include "Player/player.h"
#include "WorldMap/tilemap.h"
#include "WorldMap/tilemap_constants.h"

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include <QBuffer>
#include <QByteArray>
#include <QEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

#include <algorithm>
#include <vector>

class GameWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
  private:
    const TileMap *worldMap;
    Player *player;

    sf::View view;
    sf::Color clearColor;
    sf::Texture mapTexture;
    sf::Sprite canvasSprite;

    QTimer timer;

    bool isInited;

  public:
    explicit GameWidget(QWidget *parent = nullptr);

    void initMapPlayer(const TileMap *, Player *);
    void drawMap();

  private:
    virtual QPaintEngine *paintEngine() const override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

    virtual void mousePressEvent(QMouseEvent *) override;

    void calculatePath(GYM::fpos);
    void movePlayer(GYM::ipos);

  private slots:
    void onTimeout();
};

#endif // GAMEWIDGET_H
