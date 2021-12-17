#include "spawnermap.h"

SpawnerMap::SpawnerMap(Point2D<size_t> _shape)
{
    // Создаем двумерный массив спавнеров
    // на каждый чанк возможно по одному

    shape.x = _shape.x / GYM::chunkSize;
    shape.y = _shape.y / GYM::chunkSize;

    for (size_t i = 0; i < shape.x; ++i)
    {
        SpawnerArray spawnerChunk(shape.y);

        _map.push_back((spawnerChunk));
    }
}

void SpawnerMap::initializeSpawners(const TileMap *WM)
{
    // инициализируем спавнеры
    for (size_t i = 0; i < shape.x; ++i)
    {
        for (size_t j = 0; j < shape.y; ++j)
        {
            // этим условием конролируем число спавнеров и их распространнёность
            // на данном этапе реализовано так, в дальнейшем расположение спавнеров и их тип
            // будем выбирать случайно и в зависимости от Местности (WorldMap)
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
    // Функция, которая должна возвращать локальные спавнеры,
    // однако, сейчас она возвращает все спавнеры т.к. есть трудности
    // с представлением спавнеров , возникшие из-за недостатка времени
    // на реализацию этого класса
    SpawnerArray localMap;

    for (size_t i = 0; i < shape.x; ++i)
    {
        for (size_t j = 0; j < shape.y; ++j)
        {
            if (_map[i][j])
                localMap.push_back(_map[i][j]);
        }
    }

    return localMap;
}
