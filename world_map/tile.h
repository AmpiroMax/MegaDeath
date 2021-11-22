#ifndef TILE_H
#define TILE_H


#include <cstdint>
#include <fstream>


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

    friend std::ostream& operator << (std::ostream& output, const Tile& tile);
    friend std::istream& operator >> (std::istream& input, Tile& tile);

private:

    std::uint16_t _tile;

    void _replaceGroupOfBits(std::uint16_t targetBits, std::uint16_t newValue,
        std::uint16_t maxValue, std::uint16_t shift);
};


#endif // TILE_H
