#ifndef TILEMAP_CONSTANTS
#define TILEMAP_CONSTANTS

#include <utility>


//


using TileMatrix = std::vector<std::vector<Tile>>;			// ������� ������ ������
using CellVector = std::vector<std::pair<int, int>>;		// ������ ��������� �����	
															// first - ����� ������, second - ����� �������
using Cell = std::pair<int, int>;							// ����: first - ����� ������, second - ����� �������
using Shape = std::pair<int, int>;							// ����: first - �����, second - ������
using QueueNode = std::pair<double, Cell>;


constexpr Shape ELEMENTARY_SHAPE(0, 0);						// ���� �����, ���� �������� == ������ �����
constexpr Cell SIGNAL_CELL(-1, -1);


#endif // !TILEMAP_CONSTANTS
