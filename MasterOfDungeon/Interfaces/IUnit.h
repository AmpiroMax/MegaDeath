#ifndef IUNIT_H
#define IUNIT_H

#include "Structures/structs.h"
#include "WorldMap/tilemap_constants.h"

#include <SFML/Graphics.hpp>

class IUnit : public sf::RectangleShape
{
  private:
    GYM::stats characteristics;
    CellVector path;

  protected:
    sf::Texture *unitTexture;

  public:
    GYM::fpos getCoordinate() { return {getPosition().x, getPosition().y}; }
    GYM::stats getCharacteristics() { return characteristics; }

    void setCoordinate(const GYM::fpos &_coord) { setPosition(_coord.x, _coord.y); }
    void setCharacteristics(const GYM::stats &_characteristics) { characteristics = _characteristics; }

    virtual void drawUnit(sf::RenderTarget &target_window) const = 0;
    virtual void updateUnit() = 0;
    virtual void moveUnit() = 0;
};

#endif // IUNIT_H
