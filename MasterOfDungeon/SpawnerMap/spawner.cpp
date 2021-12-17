#include "spawner.h"

Spawner::Spawner()
{
    maxUnitCount = 1;
    currentUnitCount = 0;
    spawnerType = -1;
}

void Spawner::setSpawnerType(int SPType)
{
    spawnerType = SPType;
}

void Spawner::setSpawnerPosition(Cell _position)
{
    position = _position;
}

int Spawner::getSpawnerType()
{
    return spawnerType;
}

Enemy *Spawner::createEnemy()
{
    if (currentUnitCount == maxUnitCount)
        return nullptr;
    currentUnitCount += 1;
    Director director(position);

    IEnemyBuilder *builder;

    switch (spawnerType)
    {
        case 1:
        {
            builder = new GolemBuilder;
            break;
        }
        case 2:
        {
            builder = new SkeletonBuilder;
            break;
        }
        default:
        {
            builder = new GolemBuilder;
            break;
        }
    }

    if (currentUnitCount == 2)
        director.constructCrazyEnemy(builder);
    else
        director.constructNormalEnemy(builder);

    return builder->getResult();
}
