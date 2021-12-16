#ifndef MATH_LIB_H
#define MATH_LIB_H

/*
////////////////////////////////////////////////////////////////////////////////
 В этом файле хранятся все функции, используемые для математических расчётов
////////////////////////////////////////////////////////////////////////////////
*/

#include "Interfaces/IUnit.h"
#include "Structures/structs.h"

using namespace GYM;

bool isCoordInArea(Point2D<int> coord, Point2D<int> topLim, Point2D<int> bttmLim);

Point2D<int> getUnitPixelPos(const IUnit *unit);
Point2D<int> getUnitChunkPos(const IUnit *unit);
Point2D<int> getUnitTilePos(const IUnit *unit);
Point2D<int> convertTilePosToPixelPos(Point2D<int> pos);
Point2D<int> convertChunkPosToPixelPos(Point2D<int> pos);
Point2D<int> convertPixelPosToChunkPos(Point2D<int> pos);
Point2D<int> convertPixelPosToTilePos(Point2D<int> pos);
Point2D<int> convertPixelPosToNonPixel(Point2D<int> pos, int segmentation);
Point2D<int> convertNonPixelPosToPixel(Point2D<int> pos, int segmentation);

#endif // MATH_LIB_H
