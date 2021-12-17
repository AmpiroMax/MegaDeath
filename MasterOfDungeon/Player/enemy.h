#ifndef ENEMY_H
#define ENEMY_H

#include "Interfaces/IUnit.h"

#include "MathLib/math_lib.h"

#include <QBuffer>
#include <QByteArray>
#include <QPixmap>

class Enemy : public IUnit
{
  private:
    int logicState;

  public:
    Enemy();

    void setEnemyTexture(QString textureName);
    void updateLogicState(const Cell &playerPos);
    int getLogicState();
};

#endif // ENEMY_H
