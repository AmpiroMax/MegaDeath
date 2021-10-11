#include <cassert>


#include "tile_constants.h"
#include "tile.h"


Tile::Tile(std::uint16_t tile):
	_tile(tile) {}


Tile::Tile(): Tile(NIL) {}


void Tile::setKnowledgeBit(bool knowlege)
/*
	Эта функция устанавливает значения бита, 
	отвечающего за разведонность территории

	:param: bool knowlege - true - если тайл разведан

	:return: ничего
*/
{
	(knowlege) ? _tile |= KNOWLEDGE_MASK : _tile &= (~KNOWLEDGE_MASK);
}


void Tile::setPassabilityBit(bool passible)
/*
	Эта функция устанавливает значения бита, 
	отвечающего за проходимость территории

	:param: bool passible - true - если тайл проходим

	:return: ничего
*/
{
	(passible) ? _tile |= PASSABILITY_MASK : _tile &= (~PASSABILITY_MASK);
}


void Tile::setTextureId(std::uint16_t id)
/*
	Эта функция устанавливает значения битов, 
	кодирующих номер ID текстуры

	:param: std::uint16_t id - id текстуры(от 0 до 1023)

	:return: ничего
*/
{
	_replaceGroupOfBits(TEXTURE_ID_MASK, id, MAX_ID, TEXTURE_SHIFT);
}


void Tile::setIlluminationLevel(std::uint16_t level)
/*
	Эта функция устанавливает значения битов, 
	кодирующих уровень освещённости

	:param: std::uint16_t level - уровень освещённости(от 0 до 7)

	:return: ничего
*/
{
	_replaceGroupOfBits(ILLUMINATION_MASK, level, 
		MAX_ILLUMINATION, ILLUMINATION_SHIFT);
}


bool Tile::isKnown() const
/*
	Эта функция позволяет получить информацию
	о разведанности территории

	:param: нет параметров

	:return: true, если территория разведана
*/
{
	return (_tile & KNOWLEDGE_MASK);
}


bool Tile::isPassible() const
/*
	Эта функция позволяет получить информацию
	о проходимости территории

	:param: нет параметров

	:return: true, если территория проходима
*/
{
	return (_tile & PASSABILITY_MASK);
}


std::uint16_t Tile::getTextureId() const
/*
	Эта функция позволяет получить ID текстуры,
	накладываемой на данный тайл

	:param: нет параметров

	:return: id текстуры - число от 0 до 1023
*/
{
	return ((_tile & TEXTURE_ID_MASK) >> TEXTURE_SHIFT);
}


std::uint16_t Tile::getIlluminationLevel() const
/*
	Эта функция позволяет получить уровень
	освещённости на данном тайле

	:param: нет параметров

	:return: уровень освещённости - число от 0 до 7
*/
{
	return ((_tile & ILLUMINATION_MASK) >> ILLUMINATION_SHIFT);
}


void Tile::_replaceGroupOfBits(std::uint16_t targetBits, std::uint16_t newValue,
	std::uint16_t maxValue, std::uint16_t shift)
/*
	Вспомогательная функция, для замены определённых битов

	:param: std::uint16_t targetBits - битовая маска, для получения нужных битов
	:param: std::uint16_t newValue - новое значение заменяемых битов
	:param: std::uint16_t maxValue - ограничение на новое значение
	:param: std::uint16_t shift - значение сдвига для нового значения, 
					необходимо, чтобы заменить нужные биты

	:return: ничего
*/
{
	assert(newValue <= maxValue, ":ERROR: maximum value is exceeded");

	_tile &= (~targetBits);
	_tile |= (newValue << shift);
}
