#ifndef GAME_H
#define GAME_H

#include "IUnit.h"
#include "worldmap.h"

class Game
{
  private:
    static int gamesCount; // Game - singleton объект, поэтому
                           // добавлено статическое поле
    WorldMap *gameMap;     // Указатель на игровую карту

  public:
    Game();

    void gameLoop();
};

#endif // GAME_H
