#ifndef TILE_CONSTANTS
#define TILE_CONSTANTS


#include <cstdint>


constexpr std::uint16_t NIL = 0;					// двухбайтовый ноль

constexpr std::uint16_t TEXTURE_SHIFT = 5;			// значение сдвига для получения ID текстуры
constexpr std::uint16_t ILLUMINATION_SHIFT = 2;		// значение сдвига для получения освещённости

constexpr std::uint16_t MAX_ILLUMINATION = 7;		// максимальное значение освещённости
constexpr std::uint16_t MAX_ID = 0x03FF;			// максимальное значение ID

constexpr std::uint16_t PASSABILITY_MASK = 0x8000;	// маска для получения бита проходимости
constexpr std::uint16_t TEXTURE_ID_MASK = 0x7FE0;	// маска для получения битов ID текстуры
constexpr std::uint16_t ILLUMINATION_MASK = 0x001C;	// маска для получения уровня освещённости
constexpr std::uint16_t KNOWLEDGE_MASK = 0x0002;	// маска для получения бита разведонности территории


#endif // !TILE_CONSTANTS
