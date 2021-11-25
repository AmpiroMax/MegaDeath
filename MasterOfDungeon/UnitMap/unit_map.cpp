#include "MathLib/math_lib.h"
#include "unit_map.h"


UnitMap::UnitMap(Point2D<int> shape)
{
    for (int i = 0; i < shape.x; ++i)
    {
        UnitChunks unitChunk(shape.y);

        _map.push_back((unitChunk));
    }
}


Point2D<int> UnitMap::shape() const
/*
  Эта функция возвращает размеры карты

  :param: нет параметров

  :return: Point2D<int> - размеры. x - число строк, y - число столбцов
*/
{
    Point2D<int> shape;

    if (!_map.empty())
    {
        shape.x = _map.size();
        shape.y = _map[0].size();
    }

    return shape;
}


void UnitMap::addUnit(IUnit *unit)
{
    if (unit)
    {
        Point2D<int> pos = getUnitChunkPos(unit);
        Point2D<int> shp = shape();
        Point2D<int> nil;

        if (isCoordInArea(pos, shp, nil))
            _map[pos.x][pos.y][unit] = unit;
    }
}


void UnitMap::deleteUnit(IUnit *unit)
{
    if (unit)
    {
        Point2D<int> pos = getUnitChunkPos(unit);
        Point2D<int> shp = shape();
        Point2D<int> nil;

        if (isCoordInArea(pos, shp, nil))
        {
            auto search = _map[pos.x][pos.y].find(unit);

            if (search != _map[pos.x][pos.y].end())
                _map[pos.x][pos.y].erase(unit);
        }
    }
}


void UnitMap::moveUnit(Point2D<int> from, IUnit* unit)
{
    if (!unit) return;

    Point2D<int> shp = shape();
    Point2D<int> nil;

    if (isCoordInArea(from, shp, nil))
    {
        auto search = _map[from.x][from.y].find(unit);

        if (search != _map[from.x][from.y].end())
        {
            _map[from.x][from.y].erase(unit);
            addUnit(unit);
        }
    }
}


UnitChunk UnitMap::getLocalUnitMap(Point2D<int> chunkPos) const
{
    UnitChunk localMap;
    Point2D<int> shp = shape();
    Point2D<int> nil;

    if (isCoordInArea(chunkPos, shp, nil))
        localMap = _map[chunkPos.x][chunkPos.y];

    return localMap;
}


bool UnitMap::isAnybodyThere(Point2D<int> tilePos) const
{
    Point2D<int> pxlPos = convertTilePosToPixelPos(tilePos);
    Point2D<int> pos = convertPixelPosToChunkPos(pxlPos);
    Point2D<int> shp = shape();
    Point2D<int> nil;

    if (isCoordInArea(pos, shp, nil))
    {
        UnitChunk chunk = _map[pos.x][pos.y];

        for (auto it = chunk.begin(); it != chunk.end(); ++it)
        {
            if (getUnitTilePos(it->second) == tilePos)
                return true;
        }
    }

    return false;
}
