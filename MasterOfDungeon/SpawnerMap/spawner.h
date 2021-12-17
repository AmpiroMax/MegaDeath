#ifndef SPAWNER_H
#define SPAWNER_H

#include "Player/enemy.h"
#include "WorldMap/tilemap_constants.h"

#include "SpawnerMap/Director/director.h"
#include "SpawnerMap/Director/golembuilder.h"
#include "SpawnerMap/Director/skeletonbuilder.h"

class Spawner
{
  private:
    Cell position;

    int maxUnitCount;
    int currentUnitCount;
    int spawnerType;

  public:
    Spawner();
    void setSpawnerType(int SPType);
    void setSpawnerPosition(Cell position);

    int getSpawnerType();

    Enemy *createEnemy();
};

#endif // SPAWNER_H
