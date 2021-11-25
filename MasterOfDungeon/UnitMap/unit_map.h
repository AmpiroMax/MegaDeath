#ifndef UNIT_MAP_H
#define UNIT_MAP_H


#include <vector>


#include "unit_map_constants.h"
#include "Structures/structs.h"
#include "WorldMap/tile/tile.h"


class UnitMap
{
public:

    explicit UnitMap(Point2D<int> shape);

    UnitMap(const UnitMap&) = delete;
    UnitMap& operator= (const UnitMap&) = delete;

    void addUnit(IUnit* unit);
    void deleteUnit(IUnit* unit);
    void moveUnit(Point2D<int> from, IUnit* unit);

    UnitChunk getLocalUnitMap(Point2D<int> chunkPos) const;
    bool isAnybodyThere(Point2D<int> tilePos) const;
    Point2D<int> shape() const;

private:

    UnitChunkMap _map;

};

#endif // UNIT_MAP_H
