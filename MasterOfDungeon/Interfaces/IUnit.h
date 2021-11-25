#ifndef IUNIT_H
#define IUNIT_H

#include "Structures/structs.h"
#include "WorldMap/tilemap_constants.h"
#include "math.h"

#include <SFML/Graphics.hpp>

class IUnit : public sf::RectangleShape
{
  private:
    GYM::stats characteristics;
    GYM::fpos velocity;
    CellVector path;

    bool isAinAreaOfB(GYM::fpos A, GYM::fpos B);
    GYM::fpos getUnitVector(GYM::fpos A, GYM::fpos B);
    void changeTextureRect(int movementDirection);
    int getMovementId(float dx, float dy);

  protected:
    sf::Texture unitTexture;
    GYM::ipos textureId;
    int textureTick;
    int currentTextureTick;

  public:
    IUnit();
    GYM::stats getCharacteristics();
    void setCharacteristics(const GYM::stats &_characteristics);
    void setPath(const CellVector &_path);
    void setVelocity(const GYM::fpos &_velocity);
    void moveUnit();
};

#endif // IUNIT_H
