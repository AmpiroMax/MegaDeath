#include <algorithm>
#include <iostream>


#include "pch.h"


Map::Map(const IntMatrix& map) : _map(map) {}


Coord Map::shape() const
{
	if (_map.empty()) return { 0, 0 };

	else
		return { _map.size(), _map[0].size() };
}


IntMatrix Map::getLocalMap(Coord coord, int topLen, int bttmLen,
	int leftLen, int rightLen) const
{
	IntMatrix localMap;
	Coord shp = shape();

	if (_isCoordCorrect(coord, shp, { 0, 0 }))
	{
		int topMax = std::min(coord.first + topLen, shp.first);
		int topMin = std::max(coord.first - bttmLen, 0);
		int horMin = std::max(coord.second - leftLen, 0);
		int horMax = std::min(coord.second + rightLen, shp.second);

		for (int i = topMin; i < topMax; ++i)
		{
			std::vector<int> line;

			for (int j = horMin; j < horMax; ++j)
			{
				line.push_back(_map[i][j]);
			}

			localMap.push_back(line);
		}
	}

	return localMap;
}


IntMatrix Map::getCentredLocalMap(Coord centre, int vertLen, int horLen) const
{
	return getLocalMap(centre, vertLen, vertLen, horLen, horLen);
}


bool Map::_isCoordCorrect(Coord coord, Coord top, Coord bttm) const
{
	if ((coord.first < bttm.first) || (coord.first >= top.first))
		return false;

	if ((coord.second < bttm.second) || (coord.second >= top.second))
		return false;

	return true;
}


void printMatrix(const IntMatrix& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; matrix[i].size(); ++j)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}
