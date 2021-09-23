#ifndef WORLDMAP_H
#define WORLDMAP_H

/* TO DO

1) Переписать указатели на умные
2) Заменить в UnitChunk контейнер vector на другой с быстрым удалением

*/

#include "IUnit.h"
#include "structs.h"

typedef std::vector<IUnit *> UnitChunk;
typedef std::vector<std::vector<UnitChunk>> UnitMap;

typedef std::vector<char> GraphicChunk;
typedef std::vector<std::vector<GraphicChunk>> GraphicMap;

class WorldMap
{
  private:
    UnitMap *globalUnitMap; // карта для хранения игровых, отрисовываемых объектов
    GraphicMap *globalGraphicMap; // ландшавт карты

    size_t localMapSize = 5;             // Измеряется в Чанках
    std::pair<size_t, size_t> playerPos; // i, j индексы номера Чанка,
                                         // в котором сейча находится игрок

    std::string mapFileName; // файл, из которого будет считываться ландшавт карты

  public:
    WorldMap();

    // функция инициализирующая карты
    // возвращает код ошибки
    int initialize();

    UnitMap *getUnitMap() { return globalUnitMap; }
    GraphicMap *getGraphicMap() { return globalGraphicMap; }

    // Обновляет положение Юнитов
    // Просматривает всех Юнитов в локальной части карты (той, где сейчас игрок)
    // проверяет их положение и в случае, если Юнит оказался вне своего чанка
    // удаляет его указатель из прошлого чанка и добавляет в новый
    void updateUnitsPos();
};

#endif // WORLDMAP_H
