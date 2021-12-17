#ifndef IENEMYBUILDER_H
#define IENEMYBUILDER_H

#include "Player/enemy.h"
#include "Structures/structs.h"

#include <QString>

// Интерефейсный класс, который описывает по каким правилам
// будут создаваться объекты Enemy

class IEnemyBuilder
{
  public:
    virtual void reset() = 0;
    virtual void setCharacteristics(const GYM::stats &characteristics) = 0;
    virtual void setVelocity(const GYM::fpos &_velocity) = 0;
    virtual void setEnemyPosition(GYM::fpos pos) = 0;
    virtual void setTexture(QString textureName) = 0;
    virtual Enemy *getResult() = 0;
};

#endif // IENEMYBUILDER_H
