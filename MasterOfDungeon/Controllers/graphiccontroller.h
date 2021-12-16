#ifndef GRAPHICCONTROLLER_H
#define GRAPHICCONTROLLER_H

#include "Game/gamewidget.h"
#include "Player/player.h"
#include "UnitMap/unit_map.h"
#include "WorldMap/tilemap.h"

#include "Controllers/playercontroller.h"

#include "MathLib/math_lib.h"

#include <algorithm>

class GraphicController : public QObject
{
    Q_OBJECT
  private:
    GameWidget *gameWidget;
    const TileMap *WM;
    const UnitMap *UM;

    const Player *player;
    PlayerController *PLC;

  public:
    GraphicController();

    void initParametrs(GameWidget *, const TileMap *, const UnitMap *, const Player *, PlayerController *);
    void onTimeOutEvent();

  private:
    void processMouseEvents(Cell);
    void paint();

  private slots:
    void onPaintEvent();
    void onMouseClickEvent(GYM::Point2D<int>);
    void onShowEvent();
    void onResizeEvent();
};

#endif // GRAPHICCONTROLLER_H
