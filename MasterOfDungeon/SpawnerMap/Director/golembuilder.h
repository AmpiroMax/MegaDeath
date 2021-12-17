#ifndef GOLEMBUILDER_H
#define GOLEMBUILDER_H

#include "Interfaces/IEnemyBuilder.h"
#include "Player/Enemies/golem.h"

class GolemBuilder : public IEnemyBuilder
{
  private:
    Golem *enemy;

  public:
    GolemBuilder();

    virtual void reset();
    virtual void setCharacteristics(const GYM::stats &characteristics);
    virtual void setVelocity(const GYM::fpos &_velocity);
    virtual void setEnemyPosition(GYM::fpos pos);
    virtual void setTexture(QString textureName);
    virtual Enemy *getResult();

    ~GolemBuilder() {}
};

#endif // GOLEMBUILDER_H
