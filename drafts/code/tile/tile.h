#ifndef TILE
#define TILE


#include <cstdint>


class Tile
{
public:

	explicit Tile();
	explicit Tile(std::uint16_t tile);

	void setKnowledgeBit(bool knowledge);
	void setPassabilityBit(bool passible);
	void setTextureId(std::uint16_t id);
	void setIlluminationLevel(std::uint16_t level);

	bool isKnown() const;
	bool isPassible() const;
	std::uint16_t getTextureId() const;
	std::uint16_t getIlluminationLevel() const;

private:

	std::uint16_t _tile;

	void _replaceGroupOfBits(std::uint16_t targetBits, std::uint16_t newValue,
		std::uint16_t maxValue, std::uint16_t shift);
};


#endif // !TILE
