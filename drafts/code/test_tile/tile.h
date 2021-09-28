#ifndef TILE
#define TILE


#include <cstdint>


constexpr std::uint16_t PASSABILITY_MASK = 0x8000;
constexpr std::uint16_t TEXTURE_ID_MASK = 0x7FE0;
constexpr std::uint16_t ILLUMINATION_MASK = 0x001C;
constexpr std::uint16_t KNOWLEDGE_MASK = 0x0002;


class Tile
{
public:

	explicit Tile();
	explicit Tile(std::uint16_t tile);

	Tile(const Tile&) = delete;
	Tile& operator= (const Tile&) = delete;

	bool isKnown() const;
	bool isPassible() const;
	std::uint16_t getTextureId() const;
	std::uint16_t getIlluminationLevel() const;

private:

	std::uint16_t _tile;
};


#endif // !TILE
