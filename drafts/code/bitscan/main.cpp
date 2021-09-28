#include <iostream>
#include <cassert>


#include "bitscan.h"


int main()
{
    Tile my_tile = 0x95080000;
    assert(isPassable(my_tile));

    std::uint32_t i = getRow(my_tile);
    assert(i == 5);

    std::uint32_t j = getColumn(my_tile);
    assert(j == 8);

    std::uint32_t illumination = getIllumination(my_tile);
    assert(illumination == 2);
}
