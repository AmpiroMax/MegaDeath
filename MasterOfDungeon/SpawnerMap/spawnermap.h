#ifndef SPAWNERMAP_H
#define SPAWNERMAP_H

#include "SpawnerMap/spawner_map_constants.h"
#include "WorldMap/tilemap.h"

class SpawnerMap
{
  private:
    SpawnerMatrix _map;
    Point2D<size_t> shape;

  public:
    SpawnerMap(Point2D<size_t> shape);
    void initializeSpawners(const TileMap *WM);

    SpawnerArray getLocalSpawnersMap(Point2D<int> chunkPos, int AreaLen);
};

#endif // SPAWNERMAP_H
