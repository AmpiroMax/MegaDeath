#include "skeletonbuilder.h"

SkeletonBuilder::SkeletonBuilder()
{
    enemy = new Skeleton();
}

void SkeletonBuilder::reset()
{
    enemy = new Skeleton();
}

void SkeletonBuilder::setCharacteristics(const stats &characteristics)
{
    enemy->setCharacteristics(characteristics);
}

void SkeletonBuilder::setVelocity(const GYM::fpos &_velocity)
{
    enemy->setVelocity(_velocity);
}

void SkeletonBuilder::setEnemyPosition(fpos pos)
{
    enemy->setPosition(pos.x, pos.y);
}

void SkeletonBuilder::setTexture(QString textureName)
{
    QString textureDirectory = ":/media/unitsTextures/skeleton/" + textureName + "_skeleton.png";
    enemy->setEnemyTexture(textureDirectory);
}

Enemy *SkeletonBuilder::getResult()
{
    Skeleton *product = enemy;
    reset();
    return product;
}
