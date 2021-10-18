#include <iostream>


#include "tilemap.h"


void printCells(const CellVector& cells)
{
	for (auto& cell : cells)
		std::cout << cell.first << ", " << cell.second << std::endl;

	std::cout << std::endl;
}


int main()
{
	TileMatrix matrix;

	for (size_t i = 0; i < 5; ++i)
	{
		std::vector<Tile> vector(5, Tile(0x8000));

		matrix.push_back(vector);
	}

	for (size_t i = 0; i < 4; ++i)
		matrix[i][2].setPassabilityBit(false);


	TileMap map(matrix);

	CellVector route = map.getShortestWay({ 0, 0 }, { 4, 4});

	printCells(route);
}
