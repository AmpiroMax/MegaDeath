#ifndef TILE_MAP
#define TILE_MAP

//

#include <fstream>
#include <string>
#include <vector>


#include "C:\Users\Acer\Desktop\cpp\gamedev\master_of_dungeons\drafts\tile\tile\tile.h"
#include "tilemap_constants.h"


/* 
����������:

Tile - �������������� ������, �������� ���������, �������������,
������������� � ��������������.

Cell - ������������� ����� �� ��� ����������� �������, � ���
������ ���������� ������� (�����). �������� ������ �������
������� � ������� ������, � ������� �� ���������. 
*/


class TileMap
{
public:

	explicit TileMap(const TileMatrix& map);
	explicit TileMap(const std::string& filename);

	TileMap(const TileMap&) = delete;
	TileMap& operator= (const TileMap&) = delete;

	CellVector getShortestWay(Cell from, Cell to) const;
	Shape shape() const;

	void printMap() const;

private:

	CellVector _getAdjacentCells(int x, int y) const;
	double _calculateHeuristic(Cell from, Cell to) const;

	TileMatrix _map;
};

#endif // !TEXTURE_MAP

