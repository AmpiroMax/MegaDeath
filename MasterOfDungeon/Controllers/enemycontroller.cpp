#include "enemycontroller.h"

EnemyController::EnemyController()
{
}

void EnemyController::initParametrs(UnitMap *_UM, const TileMap *_WM, const Player *_player)
{
    UM = _UM;
    WM = _WM;
    player = _player;
}

void EnemyController::onTimeOutEvent()
{
    updateLocalUnits();
}

void EnemyController::updateLocalUnits()
{
    GYM::Point2D<int> playerPos = getUnitTilePos(player);
    EnemyChunk localUM = UM->getLocalUnitMap(playerPos);

    for (auto unit : localUM)
    {
        unit.first->updateLogicState(Cell(playerPos.x, playerPos.y));
        int LS = unit.first->getLogicState();
        GYM::Point2D<int> unitPos = getUnitTilePos(unit.first);

        if (LS == 1)
        {
            CellVector path = WM->getShortestWay(Cell(unitPos.x, unitPos.y), Cell(playerPos.x, playerPos.y));
            unit.first->setPath(path);
        }

        unit.first->moveUnit();
        GYM::Point2D<int> unitChunkPos = getUnitTilePos(unit.first);
        UM->moveUnit(unitChunkPos, unit.first);
    }
}

void EnemyController::moveUnits(const UnitChunk &localUM)
{
    for (auto unit : localUM)
    {
        unit.first->moveUnit();
    }
}
