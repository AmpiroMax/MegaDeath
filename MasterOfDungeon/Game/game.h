#ifndef GAME_H
#define GAME_H

#include "Player/player.h"
#include "WorldMap/tilemap.h"
#include "gamewidget.h"

#include <QApplication>
#include <QWidget>

class Game
{
  private:
    QApplication application;
    GameWidget gameWidget;
    TileMap worldMap;
    Player player;

  public:
    Game(int argc, char *argv[]);

    void gameLoop();
};

#endif // GAME_H
