#include "director.h"

Director::Director(Cell _enemyLocation)
{
    enemyLocation = _enemyLocation;
}

void Director::constructNormalEnemy(IEnemyBuilder *builder)
{
    // Директор берет builder, который ему передали и строит Enemy с нормальнами характеристиками и параметрами

    builder->reset();

    GYM::stats normStats = {100, 100, 10, 10, 10};
    builder->setCharacteristics(normStats);

    builder->setEnemyPosition(
        GYM::fpos((enemyLocation.first + 2.5) * GYM::tileSize, (enemyLocation.second + 2.5) * GYM::tileSize));
    builder->setVelocity(GYM::fpos(2, 2));
    builder->setTexture("normal");
}

void Director::constructCrazyEnemy(IEnemyBuilder *builder)
{
    // Директор берет builder, который ему передали и строит Enemy с сумашедшими характеристиками и параметрами

    builder->reset();

    GYM::stats crazyStats = {1000, 1000, 100, 100, 100};
    builder->setCharacteristics(crazyStats);

    builder->setEnemyPosition(GYM::fpos(enemyLocation.first * GYM::tileSize, enemyLocation.second * GYM::tileSize));
    builder->setVelocity(GYM::fpos(4, 4));
    builder->setTexture("crazy");
}
