#include "spawnercontroller.h"

SpawnerController::SpawnerController()
{
    TimeTick = 50;
    currTimeTick = 0;
}

void SpawnerController::initParametrs(UnitMap *_UM, SpawnerMap *_SM, const Player *_player)
{
    UM = _UM;
    SM = _SM;
    player = _player;
}

void SpawnerController::onTimeOutEvent()
{
    currTimeTick++;

    if (currTimeTick != TimeTick)
        return;

    currTimeTick = 0;
    updateSpawners();
}

void SpawnerController::updateSpawners()
{
    GYM::Point2D<int> playerPos = getUnitChunkPos(player);
    SpawnerArray localSM = SM->getLocalSpawnersMap(playerPos, 10);

    for (auto spawner : localSM)
    {
        Enemy *newEnemy = spawner->createEnemy();
        if (newEnemy)
        {
            GYM::Point2D<int> newEnemyPos = getUnitChunkPos(newEnemy);
        }
        UM->addUnit(newEnemy);
    }
}
