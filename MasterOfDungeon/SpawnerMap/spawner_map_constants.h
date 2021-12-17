#ifndef SPAWNER_MAP_CONSTANTS_H
#define SPAWNER_MAP_CONSTANTS_H

#include <map>
#include <utility>
#include <vector>

#include "SpawnerMap/spawner.h"

using namespace GYM;

using SpawnerMatrix = std::vector<std::vector<Spawner *>>; // Двойной массив спавнеров
using SpawnerArray = std::vector<Spawner *>;               // Массив спавнеров

#endif // SPAWNER_MAP_CONSTANTS_H
