#ifndef SPAWNERCONTROLLER_H
#define SPAWNERCONTROLLER_H

#include "Player/player.h"
#include "SpawnerMap/spawner.h"

#include "SpawnerMap/spawnermap.h"
#include "UnitMap/unit_map.h"

class SpawnerController
{
  private:
    UnitMap *UM;
    SpawnerMap *SM;
    const Player *player;
    int TimeTick;
    int currTimeTick;

  public:
    SpawnerController();
    void initParametrs(UnitMap *UM, SpawnerMap *SM, const Player *player);

    void onTimeOutEvent();

  private:
    void updateSpawners();
};

#endif // SPAWNERCONTROLLER_H
