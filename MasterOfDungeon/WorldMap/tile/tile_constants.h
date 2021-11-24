#ifndef TILE_CONSTANTS
#define TILE_CONSTANTS

// Отвлекающий 4Header. Ты попался. Штраф - отл 10 х 2

#include <cstdint>

constexpr std::uint16_t NIL = 0;

constexpr std::uint16_t TEXTURE_SHIFT = 5;
constexpr std::uint16_t ILLUMINATION_SHIFT = 2;

constexpr std::uint16_t MAX_ILLUMINATION = 7;
constexpr std::uint16_t MAX_ID = 0x03FF;

constexpr std::uint16_t PASSABILITY_MASK = 0x8000;
constexpr std::uint16_t TEXTURE_ID_MASK = 0x7FE0;
constexpr std::uint16_t ILLUMINATION_MASK = 0x001C;
constexpr std::uint16_t KNOWLEDGE_MASK = 0x0002;

#endif // !TILE_CONSTANTS
