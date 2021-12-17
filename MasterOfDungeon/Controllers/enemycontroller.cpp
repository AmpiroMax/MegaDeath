#include "enemycontroller.h"

EnemyController::EnemyController()
{
}

void EnemyController::initParametrs(UnitMap *_UM, const TileMap *_WM, const Player *_player)
{
    // Назначаю свои указатели на объекты карты юнитов, игровой карты и самого игрока
    UM = _UM;
    WM = _WM;
    player = _player;
}

void EnemyController::onTimeOutEvent()
{
    // При вызове этой функции необходимо совершить все действия,
    // которые должны быть выполнены в каждом такте
    // Конкретно эта функция обновляет состояния юнитов
    updateLocalUnits();
}

void EnemyController::updateLocalUnits()
{
    //Получение локальной карты юнитов по положению игрока
    GYM::Point2D<int> playerPos = getUnitTilePos(player);
    EnemyChunk localUM = UM->getLocalUnitMap(playerPos);

    for (auto unit : localUM)
    {
        // Обновляем логическое состояние конкретного Юнита
        unit.first->updateLogicState(Cell(playerPos.x, playerPos.y));

        // Получаем новое значение логического состояния
        int LS = unit.first->getLogicState();
        GYM::Point2D<int> unitPos = getUnitTilePos(unit.first);

        // Если логическое состояние Юнита = 1, что на данном этапе соответствует атаке на игрока
        // мы должны посчитать маршрут от нынешнего положения юнита до игрока
        if (LS == 1)
        {
            CellVector path = WM->getShortestWay(Cell(unitPos.x, unitPos.y), Cell(playerPos.x, playerPos.y));
            unit.first->setPath(path);
        }

        // Двигаем юнита в игровом поле
        unit.first->moveUnit();
        // Перемещаем игрока в UnitMap из предыдущего чанка в новый
        UM->moveUnit(unitPos, unit.first);
    }
}

void EnemyController::moveUnits(const UnitChunk &localUM)
{
    // Было решено, несмотря на обновление и движение всех юнитов в одном цикле
    // вынести дополнительно перемещение юнитов
    for (auto unit : localUM)
    {
        unit.first->moveUnit();
    }
}
