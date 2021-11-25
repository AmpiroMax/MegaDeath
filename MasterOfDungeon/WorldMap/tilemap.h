#ifndef TILE_MAP
#define TILE_MAP


#include <fstream>
#include <string>
#include <vector>

#include "tile/tile.h"
#include "tilemap_constants.h"

/*
Примечание:

Tile - отрисовываемая клетка, обладает текстурой, освещённостью,
проходимостью и разведонностью.

Cell - интерпретация тайла не как физического объекта, а как
ячейки двумерного массива (карты). Обладает только номером
столбца и номером строки, в которой он храниться.
*/

class TileMap
{
  public:
    explicit TileMap(const TileMatrix &map);
    explicit TileMap(const std::string &filename);

    TileMap(const TileMap &) = delete;
    TileMap &operator=(const TileMap &) = delete;

    CellVector getShortestWay(Cell from, Cell to) const;
    TileMatrix getLocalMap(Cell coord, int topLen, int bttmLen, int leftLen,
                           int rightLen) const;
    TileMatrix getCentredLocalMap(Cell centre, int vertLen, int horLen) const;
    Shape shape() const;

    void printMap() const;

  private:
    CellVector _getAdjacentCells(int x, int y) const;
    double _calculateHeuristic(Cell from, Cell to) const;
    bool _isCoordCorrect(Cell coord, Cell topLim, Cell bttmLim) const;

    TileMatrix _map;
};

#endif // !TEXTURE_MAP
