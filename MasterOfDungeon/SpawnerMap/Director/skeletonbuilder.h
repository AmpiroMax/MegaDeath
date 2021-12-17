#ifndef SKELETONBUILDER_H
#define SKELETONBUILDER_H

#include "Interfaces/IEnemyBuilder.h"
#include "Player/Enemies/skeleton.h"

class SkeletonBuilder : public IEnemyBuilder
{
  private:
    Skeleton *enemy;

  public:
    SkeletonBuilder();

    virtual void reset();
    virtual void setCharacteristics(const GYM::stats &characteristics);
    virtual void setVelocity(const GYM::fpos &_velocity);
    virtual void setEnemyPosition(GYM::fpos pos);
    virtual void setTexture(QString textureName);
    virtual Enemy *getResult();
};

#endif // SKELETONBUILDER_H
