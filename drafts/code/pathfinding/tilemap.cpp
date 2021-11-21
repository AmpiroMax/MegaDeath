#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <map>

//


#include "tilemap.h"


TileMap::TileMap(const TileMatrix& map) :
	_map(map) {}


TileMap::TileMap(const std::string& filename)
{
	std::ifstream input(filename);

	if (input.is_open())
	{
		while (!input.eof())
		{
			std::vector<Tile> tiles;
			char ch;

			input.get(ch);

			while (ch != '\n' && !input.eof())
			{
				input.putback(ch);

				Tile tile;
				input >> std::hex >> tile;
				
				tiles.push_back(tile);

				input.get(ch);
			}

			if (!tiles.empty())
				_map.push_back(tiles);
		}
	}

	else
		std::cout << "Impossible to open " << filename << '\n';

	input.close();
}


Shape TileMap::shape() const
/*

Ёта функци€ возвращает размеры карты

:param: нет параметров

:return: std::pair<int, int> - {количество строк, количество столбцов}

*/
{
	if (_map.empty())
	{
		return ELEMENTARY_SHAPE;
	}

	else
	{
		return { _map.size(), _map[0].size() };
	}
}

// ƒоработать. „ерновой вариант. 
// ¬озвращает вектор €чеек, которые надо посетить. 
CellVector TileMap::getShortestWay(Cell from, Cell to) const
{
	std::map<Cell, double> costs;
	std::map<Cell, Cell> cameFrom; 
	std::priority_queue<QueueNode, std::vector<QueueNode>,
		std::greater<QueueNode>> queue;

	costs[from] = 0;
	cameFrom[from] = SIGNAL_CELL;
	cameFrom[to] = SIGNAL_CELL;
	queue.push({ 0, from});

	while (!queue.empty())
	{
		Cell currCell = queue.top().second;
		double currCost = costs[currCell];

		queue.pop();

		if (currCell == to) break;

		CellVector adj = _getAdjacentCells(currCell.first, currCell.second);

		for (auto& cell : adj)
		{
			double cost = currCost + 1;

			if (costs.find(cell) == costs.end() || cost < costs[cell])
			{
				double priority = cost + _calculateHeuristic(cell, to);

				costs[cell] = cost;
				cameFrom[cell] = currCell;
				queue.push({ priority, cell });
			}
		}
	}

	CellVector route;
	Cell currCell = to;

	while (currCell != SIGNAL_CELL)
	{
		route.push_back(currCell);

		currCell = cameFrom[currCell];
	}
	
	std::reverse(route.begin(), route.end());

	return route;
}


void TileMap::printMap() const
{
	for (size_t i = 0; i < _map.size(); ++i)
	{
		for (size_t j = 0; j < _map[i].size(); ++j)
		{
			if (_map[i][j].isPassible())
				std::cout << "1";

			else
				std::cout << "0";
		}

		std::cout << std::endl;
	}
}


CellVector TileMap::_getAdjacentCells(int x, int y) const
/*

Ёта функци€ возвращает вектор координат в двумерном массиве
ближайших по восьми направлени€м €чеек к данной €чейке. 

:param: int x - номер строки текущей €чейки
:param: int y - номер столбца текущей €чейки

:return: std::vector<std::pair<int, int>>

*/
{
	// преобразование координат?

	int lenght = shape().first, width = shape().second;

	CellVector adjacentCells;

	for (int i = x - 1; i < x + 2; ++i)
	{
		if (0 <= i && i < lenght)
		{
			for (int j = y - 1; j < y + 2; ++j)
			{
				if (0 <= j && j < width)
				{
					if ((i != x || j != y) && _map[i][j].isPassible())
						adjacentCells.push_back({ i, j });
				}
			}
		}
	}

	return adjacentCells;
}


double TileMap::_calculateHeuristic(Cell from, Cell to) const
{
	int x = to.first - from.first;
	int y = to.second - from.second;
	double dist = sqrt(pow(x, 2) + pow(x, 2));
	
	return dist;
}
