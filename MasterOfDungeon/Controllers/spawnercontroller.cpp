#include "spawnercontroller.h"

SpawnerController::SpawnerController()
{
    TimeTick = 50;
    currTimeTick = 0;
}

void SpawnerController::initParametrs(UnitMap *_UM, SpawnerMap *_SM, const Player *_player)
{
    // Назначаю свои указатели на объекты карты юнитов, карты спавнеров, самого игрока
    UM = _UM;
    SM = _SM;
    player = _player;
}

void SpawnerController::onTimeOutEvent()
{
    // Спавнер должен призывать мобов раз в определенное число игровых тактов
    currTimeTick++;

    if (currTimeTick != TimeTick)
        return;

    currTimeTick = 0;
    updateSpawners();
}

void SpawnerController::updateSpawners()
{
    // Получаем локальные спавнеры и говорим им создать нового противника
    GYM::Point2D<int> playerPos = getUnitChunkPos(player);
    SpawnerArray localSM = SM->getLocalSpawnersMap(playerPos, 10);

    for (auto spawner : localSM)
    {
        // Создаем противников
        Enemy *newEnemy = spawner->createEnemy();
        // Добавляем их в карту юнитов
        UM->addUnit(newEnemy);
    }
}
