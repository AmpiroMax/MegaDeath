#ifndef UNIT_MAP_CONSTANTS_H
#define UNIT_MAP_CONSTANTS_H

#include <map>
#include <utility>
#include <vector>

#include "Interfaces/IUnit.h"
#include "Player/enemy.h"

using namespace GYM;

using UnitChunkMap = std::vector<std::vector<std::map<Enemy *, Enemy *>>>;
using UnitChunks = std::vector<std::map<Enemy *, Enemy *>>;
using UnitChunk = std::map<Enemy *, Enemy *>;

using EnemyChunkMap = std::vector<std::vector<std::map<Enemy *, Enemy *>>>;
using EnemyChunks = std::vector<std::map<Enemy *, Enemy *>>;
using EnemyChunk = std::map<Enemy *, Enemy *>;
#endif // UNIT_MAP_CONSTANTS_H
