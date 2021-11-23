#ifndef LOCAL_MAP
#define LOCAL_MAP


#include <utility>
#include <vector>


using IntMatrix = std::vector<std::vector<int>>;
using Coord = std::pair<int, int>;


void printMatrix(const IntMatrix& matrix);


class Map
{
public:

	explicit Map(const IntMatrix& map);

	IntMatrix getLocalMap(Coord coord, int topLen, int bttmLen,
		int leftLen, int rightLen) const;
	IntMatrix getCentredLocalMap(Coord centre, int vertLen, int horLen) const;
	Coord shape() const;

private:

	bool _isCoordCorrect(Coord coord, Coord top, Coord bttm) const;

	IntMatrix _map;
};


#endif // !LOCAL_MAP

