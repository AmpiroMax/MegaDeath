#ifndef IUNIT_H
#define IUNIT_H

#include "IDrawObj.h"
#include "structs.h"

class IUnit : public IDrawObj
{
  public:
    gym::pos coord;
    gym::stats stats;
    gym::inventory inventory;

    std::string name;
    std::string info;
    size_t id;

    gym::pos &getCoordinate() { return coord; }
    gym::stats &getStats() { return stats; }
    gym::inventory &getInventory() { return inventory; }

    void setCoordinate(const gym::pos &_coord) { coord = _coord; }
    void setStats(const gym::stats &_stats) { stats = _stats; }
    void setInventory(const gym::inventory &_inventory) { inventory = _inventory; }

    virtual void update() = 0;
};

#endif // IUNIT_H
