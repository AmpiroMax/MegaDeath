#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <vector>

typedef std ::vector<std::vector<char>> land;

class WorldMap
{
  private:
    void initLand();

  public:
    land landScape;
    WorldMap();
};

#endif // WORLDMAP_H
