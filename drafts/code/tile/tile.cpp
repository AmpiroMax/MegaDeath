#include <cassert>


#include "tile_constants.h"
#include "tile.h"


Tile::Tile(std::uint16_t tile):
	_tile(tile) {}


Tile::Tile(): Tile(NIL) {}


void Tile::setKnowledgeBit(bool knowlege)
{
	(knowlege) ? _tile |= KNOWLEDGE_MASK : _tile &= (~KNOWLEDGE_MASK);
}


void Tile::setPassabilityBit(bool passible)
{
	(passible) ? _tile |= PASSABILITY_MASK : _tile &= (~PASSABILITY_MASK);
}


void Tile::setTextureId(std::uint16_t id)
{
	_replaceGroupOfBits(TEXTURE_ID_MASK, id, MAX_ID, TEXTURE_SHIFT);
}


void Tile::setIlluminationLevel(std::uint16_t level)
{
	_replaceGroupOfBits(ILLUMINATION_MASK, level, 
		MAX_ILLUMINATION, ILLUMINATION_SHIFT);
}


bool Tile::isKnown() const
{
	return (_tile & KNOWLEDGE_MASK);
}


bool Tile::isPassible() const
{
	return (_tile & PASSABILITY_MASK);
}


std::uint16_t Tile::getTextureId() const
{
	return ((_tile & TEXTURE_ID_MASK) >> TEXTURE_SHIFT);
}


std::uint16_t Tile::getIlluminationLevel() const
{
	return ((_tile & ILLUMINATION_MASK) >> ILLUMINATION_SHIFT);
}


void Tile::_replaceGroupOfBits(std::uint16_t targetBits, std::uint16_t newValue,
	std::uint16_t maxValue, std::uint16_t shift)
{
	assert(newValue <= maxValue, ":ERROR: maximum value is exceeded");

	_tile &= (~targetBits);
	_tile |= (newValue << shift);
}


std::ostream& operator << (std::ostream& output, const Tile& tile)
{
	output << tile._tile;

	return output;
}


std::istream& operator >> (std::istream& input, Tile& tile)
{
	input >> tile._tile;

	return input;
}
