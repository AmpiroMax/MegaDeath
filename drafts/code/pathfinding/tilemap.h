#ifndef TILE_MAP
#define TILE_MAP


#include <vector>


#include "C:\Users\Acer\Desktop\cpp\gamedev\master_of_dungeons\drafts\tile\tile\tile.h"
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

	explicit TileMap(const TileMatrix& map);

	TileMap(const TileMap&) = delete;
	TileMap& operator= (const TileMap&) = delete;

	CellVector getShortestWay(Cell from, Cell to) const;
	Shape shape() const;

private:

	CellVector _getAdjacentCells(int x, int y) const;
	double _calculateHeuristic(Cell from, Cell to) const;

	TileMatrix _map;
};

#endif // !TEXTURE_MAP

