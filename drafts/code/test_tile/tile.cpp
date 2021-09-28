#include "pch.h"


Tile::Tile(std::uint16_t tile) :
	_tile(tile) {}


Tile::Tile() : Tile(0x0000) {}


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
	return ((_tile & TEXTURE_ID_MASK) >> 5);
}


std::uint16_t Tile::getIlluminationLevel() const
{
	return ((_tile & ILLUMINATION_MASK) >> 2);
}
