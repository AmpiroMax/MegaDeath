#ifndef TILEMAP_CONSTANTS
#define TILEMAP_CONSTANTS

#include <utility>
#include <vector>

#include "tile/tile.h"

//

using TileMatrix = std::vector<std::vector<Tile>>;   // двойной массив тайлов
using CellVector = std::vector<std::pair<int, int>>; // вектор координат ячеек
                                                     // first - номер строки, second - номер столбца
using Cell = std::pair<int, int>;                    // пара: first - номер строки, second - номер столбца
using Shape = std::pair<int, int>;                   // пара: first - длина, second - ширина
using QueueNode = std::pair<double, Cell>;

constexpr Shape ELEMENTARY_SHAPE(0, 0);              // ноль строк, ноль столбцов == пустая карта
constexpr Cell SIGNAL_CELL(-1, -1);

#endif // !TILEMAP_CONSTANTS
