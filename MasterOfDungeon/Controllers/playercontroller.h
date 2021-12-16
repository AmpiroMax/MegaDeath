#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Player/player.h"
#include "UnitMap/unit_map.h"
#include "WorldMap/tilemap.h"

class PlayerController
{
  private:
    Player *player;
    const TileMap *WM;
    const UnitMap *UM;

  public:
    PlayerController();

    void initParametrs(Player *, const TileMap *, const UnitMap *);
    void recalculatePath(Cell to);
    void onTimeOutEvent();
};

#endif // PLAYERCONTROLLER_H
