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
    // Функция создающая при вызове определенного противника

    // Если число уже существующих от этого спавнера юнитов
    // равно максимальному возможному их числу, то более никого не создаем
    if (currentUnitCount == maxUnitCount)
        return nullptr;

    // Создали юнита -> увеличили из число от этого спавнера на 1
    currentUnitCount += 1;

    // Создаем директора
    Director director(position);
    // СОздаем строителя
    IEnemyBuilder *builder;

    // В зависимости от типа спавнера создаём того или ного строителя
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

    // Каждого второго юнита мы будем делать безумным
    if (currentUnitCount == 2)
        director.constructCrazyEnemy(builder);
    else
        director.constructNormalEnemy(builder);

    // Возвращаем нового юнита, которого мы создали
    return builder->getResult();
}
