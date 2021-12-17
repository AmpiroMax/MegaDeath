#include "playercontroller.h"

#include "MathLib/math_lib.h"
#include "Structures/structs.h"

PlayerController::PlayerController()
{
}

void PlayerController::initParametrs(Player *_player, const TileMap *_WM, const UnitMap *_UM)
{
    // Назначаю свои указатели на объекты карты юнитов, игровой карты, самого игрока
    player = _player;
    WM = _WM;
    UM = _UM;

    // Устанавливаю определенные координаты игроку и задаю ему скорость
    player->setPosition(GYM::tileSize * 13.5, GYM::tileSize * 13.5);
    player->setVelocity(GYM::fpos(3, 3));
}

void PlayerController::recalculatePath(Cell to)
{
    // При вызове это функции пересчитываем маршрут для игрока из его
    // текущего положения в то, которое сказано в параметре функции
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell from = {tmp.x, tmp.y};

    CellVector newPath = WM->getShortestWay(from, to);
    player->setPath(newPath);
}

void PlayerController::onTimeOutEvent()
{
    // На каждый игровой тик необходимо подвигать игрока
    player->moveUnit();
}
