#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>

#include <QFile>
#include <QString>

//

#include "tilemap.h"

TileMap::TileMap(const TileMatrix &map) : _map(map)
{
}

TileMap::TileMap(const std::string &filename)
/*

  Конструктор для создания карты по txt-файлу

  :param: const std::string& filename - имя файла для чтения

  :return: ничего не возвращаяет

*/
{
    QFile input(QString::fromStdString(filename));

    if (!input.open(QIODevice::ReadOnly))
    {
        std::cout << "Impossible to open " << filename << '\n';
        return;
    }

    while (!input.atEnd())
    {
        std::vector<Tile> tiles;
        uint16_t tileNumber;

        QString line = input.readLine();
        QStringList fields = line.split(" ");

        for (auto field : fields)
        {
            bool ok;
            tileNumber = field.toUShort(&ok, 16);
            Tile Tile(tileNumber);

            tiles.push_back(Tile);
        }
        _map.push_back(tiles);
    }

    input.close();
}

Shape TileMap::shape() const
/*

Эта функция возвращает размеры карты

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
        return {_map.size(), _map[0].size()};
    }
}

// Доработать. Черновой вариант.
// Возвращает вектор ячеек, которые надо посетить.
CellVector TileMap::getShortestWay(Cell from, Cell to) const
{
    std::map<Cell, double> costs;
    std::map<Cell, Cell> cameFrom;
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> queue;

    costs[from] = 0;
    cameFrom[from] = SIGNAL_CELL;
    cameFrom[to] = SIGNAL_CELL;
    queue.push({0, from});

    while (!queue.empty())
    {
        Cell currCell = queue.top().second;
        double currCost = costs[currCell];

        queue.pop();

        if (currCell == to)
            break;

        CellVector adj = _getAdjacentCells(currCell.first, currCell.second);

        for (auto &cell : adj)
        {
            double cost = currCost + 1;

            if (costs.find(cell) == costs.end() || cost < costs[cell])
            {
                double priority = cost + _calculateHeuristic(cell, to);

                costs[cell] = cost;
                cameFrom[cell] = currCell;
                queue.push({priority, cell});
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
/*

  Функция для отладки (удалить по заверщении проекта)
  Печатает карту по следующему принципу:
  - Если поле проходимо - печатает "1";
  - Если поле непроходимо - печатает "0"

  :param: нет параметров

  :return: ничего не возвращает

 */
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

TileMatrix TileMap::getLocalMap(Cell coord, int topLen, int bttmLen, int leftLen, int rightLen) const
/*

  Эта функция возвращает локальну карту следующего размера:
  [coord.i - bttmLen; coord.i + topLen - 1] x
  [coord.j - leftLen; coord.j + rightLen - 1]

  :param: Cell coord - базовая точка, от которой отсчитываются смещения
  :param: int topLen - смещение вверх по i
  :param: int bttmLen - смещение вниз по i
  :param: int leftLen - смещение влево по j
  :param: int rightLen - смещение вправо по j

  :return: TileMatrix - локальная карта

*/
{
    TileMatrix localMap;
    Shape shp = shape();

    if (_isCoordCorrect(coord, shp, {0, 0}))
    {
        int vertMax = std::min(coord.first + topLen, shp.first);
        int vertMin = std::max(coord.first - bttmLen, 0);
        int horMin = std::max(coord.second - leftLen, 0);
        int horMax = std::min(coord.second + rightLen, shp.second);

        for (int i = vertMin; i < vertMax; ++i)
        {
            std::vector<Tile> line;

            for (int j = horMin; j < horMax; ++j)
                line.push_back(_map[i][j]);

            localMap.push_back(line);
        }
    }

    return localMap;
}

TileMatrix TileMap::getCentredLocalMap(Cell centre, int vertLen, int horLen) const
/*

  Эта функция возвращает локальну карту следующего размера:
  [centre.i - vertLen; centre.i + vertLen - 1] x
  [centre.j - horLen; centre.j + horLen - 1]

  :param: Cell centre - базовая точка, от которой отсчитываются смещения
  :param: int vertLen - смещение по i
  :param: int horLen - смещение  по j

  :return: TileMatrix - локальная карта с центром в centre

*/
{
    return getLocalMap(centre, vertLen + 1, vertLen, horLen, horLen + 1);
}

CellVector TileMap::_getAdjacentCells(int x, int y) const
/*

Эта функция возвращает вектор координат в двумерном массиве
ближайших по восьми направлениям ячеек к данной ячейке.

:param: int x - номер строки текущей ячейки
:param: int y - номер столбца текущей ячейки

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
                        adjacentCells.push_back({i, j});
                }
            }
        }
    }

    return adjacentCells;
}

double TileMap::_calculateHeuristic(Cell from, Cell to) const
/*

  Эта функция считается эвристику для алгоритма А*

  Эвристика - расстояние на плоскости

  :param: Cell from, to - координаты концов отрезков

  :return: расстояние между концами отрезков

*/
{
    int x = to.first - from.first;
    int y = to.second - from.second;
    double dist = sqrt(pow(x, 2) + pow(y, 2));

    return dist;
}

bool TileMap::_isCoordCorrect(Cell coord, Cell topLim, Cell bttmLim) const
/*

  Эта функция проверяет принадлежит ли заданная координата указанной области

  :param: Cell coord - проверяемая координата
  :param: Cell topLim - границы сверху по x и y
  :param: Cell bttmLim - границы снизу по x и y

  :return: true, если точка не выходит за границы, иначе - false

*/
{
    if ((coord.first < bttmLim.first) || (coord.first >= topLim.first))
        return false;

    if ((coord.second < bttmLim.second) || (coord.second >= topLim.second))
        return false;

    return true;
}
