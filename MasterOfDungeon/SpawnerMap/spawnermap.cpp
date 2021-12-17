#include "spawnermap.h"

SpawnerMap::SpawnerMap(Point2D<size_t> _shape)
{
    shape.x = _shape.x / GYM::chunkSize;
    shape.y = _shape.y / GYM::chunkSize;

    for (int i = 0; i < shape.x; ++i)
    {
        SpawnerArray spawnerChunk(shape.y);

        _map.push_back((spawnerChunk));
    }
}

void SpawnerMap::initializeSpawners(const TileMap *WM)
{
    for (int i = 0; i < shape.x; ++i)
    {
        for (int j = 0; j < shape.y; ++j)
        {
            if (i % 17 == 0 && j % 17 == 0)
            {
                Cell pos(i, j);
                _map[i][j] = new Spawner();
                _map[i][j]->setSpawnerPosition(pos);
                _map[i][j]->setSpawnerType(1);
            }
        }
    }
}

SpawnerArray SpawnerMap::getLocalSpawnersMap(Point2D<int> chunkPos, int AreaLen)
{
    SpawnerArray localMap;

    for (int i = 0; i < shape.x; ++i)
    {
        for (int j = 0; j < shape.y; ++j)
        {
            if (_map[i][j])
                localMap.push_back(_map[i][j]);
        }
    }

    return localMap;
}
