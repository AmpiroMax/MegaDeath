#ifndef UNIT_MAP_H
#define UNIT_MAP_H

#include <vector>

#include "Structures/structs.h"
#include "WorldMap/tile/tile.h"
#include "unit_map_constants.h"

class UnitMap
{
  public:
    explicit UnitMap(Point2D<size_t> shape);

    UnitMap(const UnitMap &) = delete;
    UnitMap &operator=(const UnitMap &) = delete;

    void addUnit(Enemy *unit);
    void deleteUnit(Enemy *unit);
    void moveUnit(Point2D<int> from, Enemy *unit);

    UnitChunk getLocalUnitMap(Point2D<int> chunkPos) const;
    bool isAnybodyThere(Point2D<int> tilePos) const;
    Point2D<int> shape() const;

  private:
    UnitChunkMap _map;
};

#endif // UNIT_MAP_H
