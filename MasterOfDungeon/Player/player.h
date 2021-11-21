#ifndef PLAYER_H
#define PLAYER_H

#include "Interfaces/IUnit.h"
#include "Structures/structs.h"

class Player : public IUnit
{
  public:
    Player();

    virtual void drawUnit(sf::RenderTarget &target_window) const override;
};

#endif // PLAYER_H
