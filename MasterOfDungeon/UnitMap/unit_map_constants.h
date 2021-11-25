#ifndef UNIT_MAP_CONSTANTS_H
#define UNIT_MAP_CONSTANTS_H


#include <utility>
#include <vector>
#include <map>


#include "Interfaces/IUnit.h"


using namespace GYM;


using UnitChunkMap = std::vector<std::vector<std::map<IUnit*, IUnit*>>>;
using UnitChunks = std::vector<std::map<IUnit*, IUnit*>>;
using UnitChunk = std::map<IUnit*, IUnit*>;


#endif // UNIT_MAP_CONSTANTS_H
