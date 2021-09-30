#ifndef IUNIT_H
#define IUNIT_H

#include "IDrawObj.h"
#include "structs.h"

class IUnit : public IDrawObj
{
  public:
    GYM::pos coord;
    GYM::stats stats;
    GYM::inventory inventory;

    std::string name;
    std::string info;
    size_t id;

    GYM::pos getCoordinate() { return coord; }
    GYM::stats getStats() { return stats; }
    GYM::inventory getInventory() { return inventory; }

    void setCoordinate(const GYM::pos &_coord) { coord = _coord; }
    void setStats(const GYM::stats &_stats) { stats = _stats; }
    void setInventory(const GYM::inventory &_inventory) { inventory = _inventory; }

    virtual void update() = 0;
};

#endif // IUNIT_H
