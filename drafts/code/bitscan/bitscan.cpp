#include "bitscan.h"


bool isPassable(const Tile tile)
{
	return (tile & PASSABILITY_MASK);
}


std::uint32_t getRow(const Tile tile)
{
	return ((tile & ROW_MASK) >> 26);
}


std::uint32_t getColumn(const Tile tile)
{
	return ((tile & COLUMN_MASK) >> 21);
}


std::uint32_t getIllumination(const Tile tile)
{
	return ((tile & ILLUMINATION_MASK) >> 18);
}
