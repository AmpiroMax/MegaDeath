#include <iostream>


#include "world_map.h"


void printCells(const CellVector& cells)
{
    for (auto& cell : cells)
        std::cout << cell.first << ", " << cell.second << std::endl;

    std::cout << std::endl;
}


int main()
{
    WorldMap map("C:\\Users\\Acer\\Desktop\\cpp\\gamedev\\master_of_dungeons\\MegaDeath\\world_map\\map1.txt");

    map.printMap();

    std::cout << std::endl;

    CellVector route = map.getShortestWay({ 0, 0 }, { 8, 15 });

    printCells(route);
}
