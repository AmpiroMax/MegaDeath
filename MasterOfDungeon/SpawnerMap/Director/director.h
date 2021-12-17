#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Interfaces/IEnemyBuilder.h"

// Класс директор - отвечает за то как будут создаваться те или иные Enemy
class Director
{
    Cell enemyLocation;

  public:
    Director(Cell _enemyLocation);
    void constructNormalEnemy(IEnemyBuilder *builder);
    void constructCrazyEnemy(IEnemyBuilder *builder);
};

#endif // DIRECTOR_H
