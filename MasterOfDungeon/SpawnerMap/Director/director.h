#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Interfaces/IEnemyBuilder.h"

class Director
{
    Cell enemyLocation;

  public:
    Director(Cell _enemyLocation);
    void constructNormalEnemy(IEnemyBuilder *builder);
    void constructCrazyEnemy(IEnemyBuilder *builder);
};

#endif // DIRECTOR_H
