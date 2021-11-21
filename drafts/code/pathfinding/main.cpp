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
	TileMap map("map1.txt");

	map.printMap();

	CellVector route = map.getShortestWay({ 0, 0 }, { 8, 15 });

	printCells(route);
}
