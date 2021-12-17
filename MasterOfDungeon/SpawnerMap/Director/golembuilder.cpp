#include "golembuilder.h"

GolemBuilder::GolemBuilder()
{
}

void GolemBuilder::reset()
{
    enemy = new Golem();
}

void GolemBuilder::setCharacteristics(const stats &characteristics)
{
    enemy->setCharacteristics(characteristics);
}

void GolemBuilder::setVelocity(const fpos &_velocity)
{
    enemy->setVelocity(_velocity);
}

void GolemBuilder::setEnemyPosition(fpos pos)
{
    enemy->setPosition(pos.x, pos.y);
}

void GolemBuilder::setTexture(QString textureName)
{
    QString textureDirectory = ":/media/unitsTextures/golem/" + textureName + "_golem.png";
    enemy->setEnemyTexture(textureDirectory);
}

Enemy *GolemBuilder::getResult()
{
    Golem *product = enemy;
    reset();
    return product;
}
