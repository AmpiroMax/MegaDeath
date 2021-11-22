#ifndef WORLD_MAP_H
#define WORLD_MAP_H


#include <fstream>
#include <string>
#include <vector>


#include "tile.h"
#include "world_map_constants.h"


/*
Примечание:

Tile - отрисовываемая клетка, обладает текстурой, освещённостью,
проходимостью и разведонностью.

Cell - интерпретация тайла не как физического объекта, а как
ячейки двумерного массива (карты). Обладает только номером
столбца и номером строки, в которой он храниться.
*/


class WorldMap
{
public:

    explicit WorldMap(const TileMatrix& map);
    explicit WorldMap(const std::string& filename);

    WorldMap(const WorldMap&) = delete;
    WorldMap& operator= (const WorldMap&) = delete;

    CellVector getShortestWay(Cell from, Cell to) const;
    Shape shape() const;

    void printMap() const;

private:

    CellVector _getAdjacentCells(int x, int y) const;
    double _calculateHeuristic(Cell from, Cell to) const;

    TileMatrix _map;
};


#endif // WORLD_MAP_H
