#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "Player/player.h"
#include "UnitMap/unit_map.h"
#include "WorldMap/tilemap.h"

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include <QBuffer>
#include <QByteArray>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QWidget>

#include <vector>

class GameWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
  private:
    sf::Texture mapTexture;
    sf::Sprite canvasSprite;
    sf::View view;

  public:
    explicit GameWidget(QWidget *parent = nullptr);

    void drawMap(const TileMatrix &localMap, const Cell playerPos);
    void drawUnits(const UnitChunk &localUnits);
    void drawPlayer(const Player *player);

    void setViewPosition(sf::Vector2f);
    void setViewSize(int width, int height);
    void setViewZoom(float zoomFactor);

  private:
    virtual QPaintEngine *paintEngine() const override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void keyPressEvent(QKeyEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

  signals:
    void paintEventSignal();
    void mouseEventSignal(GYM::Point2D<int>);
    void keyPressEventSignal(int code);
    void showEventSignal();
    void resizeEventSignal();
};

#endif // GAMEWIDGET_H
