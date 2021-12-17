#include "unit_map.h"
#include "MathLib/math_lib.h"

UnitMap::UnitMap(Point2D<size_t> shape)
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

void UnitMap::addUnit(Enemy *unit)
/*
 Эта функция добавляет переданного юнита в чанк, в котором он находится

 :param: IUnit* unit - указатель на юнита

 :return: ничего не возвращает
 */
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

void UnitMap::deleteUnit(Enemy *unit)
/*
 Эта функция удаляет переданного юнита из чанка, в котором он находится

 :param: IUnit* unit - указатель на юнита

 :return: ничего не возвращает
*/
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

void UnitMap::moveUnit(Point2D<int> from, Enemy *unit)
/*

  Эта функция перемещает данного юнита из заданного чанка в
  чанк, в котором находится юнит

  :param: Point2D<int> from - заданный чанк
  :param: IUnit* unit - заданный юнит

  :return: ничего не возвращает
*/
{
    if (!unit)
        return;

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
/*
 Эта функция возвращает словарь со всеми юнитами в данном чанке

 :param: Point2D<int> chunkPos - координаты данного чанка

 :return: UnitChunk - словарь юнитов данного чанка
*/
{
    //    UnitChunk localMap;
    //    Point2D<int> shp = shape();
    //    Point2D<int> nil;

    //    if (isCoordInArea(chunkPos, shp, nil))
    //        localMap = _map[chunkPos.y][chunkPos.x];

    //    return localMap;
    for (int i = 0; i < _map.size(); ++i)
    {
        for (int j = 0; j < _map[0].size(); ++j)
            if (_map[i][j].size() != 0)
            {
                return _map[i][j];
            }
    }
    return _map[0][0];
}

bool UnitMap::isAnybodyThere(Point2D<int> tilePos) const
/*
  Эта функция определяет, есть ли юниты в данном тайле

  :param: Point2D<int> tilePos - позиция данного тайла

  :return: true - если в тайле есть юнит, иначе - false
*/
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
            Point2D<int> currPos = getUnitTilePos(it->second);
            if (currPos == tilePos)
                return true;
        }
    }

    return false;
}
