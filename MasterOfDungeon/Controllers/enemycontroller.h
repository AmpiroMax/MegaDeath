#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Player/player.h"
#include "UnitMap/unit_map.h"
#include "UnitMap/unit_map_constants.h"
#include "WorldMap/tilemap.h"

#include "MathLib/math_lib.h"

#include <QObject>

class EnemyController
{
  private:
    UnitMap *UM;
    const TileMap *WM;
    const Player *player;

  public:
    EnemyController();

    void initParametrs(UnitMap *UM, const TileMap *WM, const Player *player);
    void onTimeOutEvent();

  private:
    void updateLocalUnits();

    void updateUnitLogicState();
    int getUnitLogicState();
    CellVector recalculatUnitPath();
    void moveUnits(const UnitChunk &localUM);
};

#endif // ENEMYCONTROLLER_H
