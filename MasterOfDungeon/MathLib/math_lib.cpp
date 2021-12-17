#include "math_lib.h"

bool isCoordInArea(Point2D<int> coord, Point2D<int> topLim, Point2D<int> bttmLim)
/*

  Эта функция проверяет принадлежит ли заданная координата указанной области

  :param: Point2D<int> coord - проверяемая координата
  :param: Point2D<int> - границы сверху по x и y
  :param: Point2D<int> - границы снизу по x и y

  :return: true, если точка не выходит за границы, иначе - false

*/
{
    if ((coord.x < bttmLim.x) || (coord.x >= topLim.x))
        return false;

    if ((coord.y < bttmLim.y) || (coord.y >= topLim.y))
        return false;

    return true;
}

Point2D<int> getUnitPixelPos(const IUnit *unit)
/*
 Эта функция расчитывает позицию юнита в пикселях

 :param: IUnit* unit - указатель на юнита

 :return: Point2D<int> - позиция в пикселях (с округлением)

 Замечание: в случае, если передан nullptr возвращает недействительные индексы
*/
{
    Point2D<int> pos(-tileSize, -tileSize);

    if (unit)
    {
        pos.x = static_cast<int>(unit->getPosition().x);
        pos.y = static_cast<int>(unit->getPosition().y);
    }

    return pos;
}

Point2D<int> getUnitChunkPos(const IUnit *unit)
/*
 Эта функция расчитывает позицию юнита в чанках

 :param: IUnit* unit - указатель на юнита

 :return: Point2D<int> - позиция в чанках

 Замечание: в случае, если передан nullptr возвращает недействительные индексы
*/
{
    Point2D<int> pos;

    if (unit)
    {
        Point2D<int> pxlPos = getUnitPixelPos(unit);
        pos = convertPixelPosToChunkPos(pxlPos);
    }

    return pos;
}

Point2D<int> getUnitTilePos(const IUnit *unit)
/*
 Эта функция расчитывает позицию юнита в тайлах

 :param: IUnit* unit - указатель на юнита

 :return: Point2D<int> - позиция в тайлах

 Замечание: в случае, если передан nullptr возвращает недействительные индексы
*/
{
    Point2D<int> pos;

    if (unit)
    {
        Point2D<int> pxlPos = getUnitPixelPos(unit);
        pos = convertPixelPosToTilePos(pxlPos);
    }

    return pos;
}

Point2D<int> convertPixelPosToChunkPos(Point2D<int> pos)
/*
  Эта функция переводит координаты текущей позиции из пикселей в чанки

  :param: Point2D<int> pos - текущая позиция в пикселях

  :return: Point2D<int> - позиция в чанках
*/
{
    return convertPixelPosToNonPixel(pos, chunkSize);
}

Point2D<int> convertPixelPosToTilePos(Point2D<int> pos)
/*
  Эта функция переводит координаты текущей позиции из пикселей в тайлы

  :param: Point2D<int> pos - текущая позиция в пикселях

  :return: Point2D<int> - позиция в тайлах
*/
{
    return convertPixelPosToNonPixel(pos, tileSize);
}

Point2D<int> convertChunkPosToPixelPos(Point2D<int> pos)
/*
  Эта функция переводит координаты текущей позиции из чанков в пиксели

  :param: Point2D<int> pos - текущая позиция в чанках

  :return: Point2D<int> - позиция в пикселях
*/
{
    return convertNonPixelPosToPixel(pos, chunkSize);
}

Point2D<int> convertTilePosToPixelPos(Point2D<int> pos)
/*
  Эта функция переводит координаты текущей позиции из тайлов в пиксели

  :param: Point2D<int> pos - текущая позиция в тайлах

  :return: Point2D<int> - позиция в пикселях
*/
{
    return convertNonPixelPosToPixel(pos, tileSize);
}

Point2D<int> convertPixelPosToNonPixel(Point2D<int> pos, int segmentation)
/*
 Эта функция переводит координаты из пикселей в другие единицы измерения

 :param: Point2D<int> pos - позиция в пикселях
 :param: int segmentation - количество пикселей в новой единице измерения

 :return: Point2D<int> - позиция в новых единицах измерения
*/
{
    if (!segmentation)
        return pos;

    Point2D convPos(pos.x / segmentation, pos.y / segmentation);

    return convPos;
}

Point2D<int> convertNonPixelPosToPixel(Point2D<int> pos, int segmentation)
/*
 Эта функция переводит координаты из данных единиц измерения в пиксели

 :param: Point2D<int> pos - позиция в данных единицах измерения
 :param: int segmentation - количество пикселей в данной единице измерения

 :return: Point2D<int> - позиция в пикселях
*/
{
    Point2D convPos(pos.x * segmentation, pos.y * segmentation);

    return convPos;
}
