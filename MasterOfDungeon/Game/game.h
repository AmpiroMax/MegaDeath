#ifndef GAME_H
#define GAME_H

#include "Player/player.h"
#include "Widgets/mainwindow.h"
#include "WorldMap/tilemap.h"

#include <QApplication>
#include <QWidget>

class Game
{
  private:
    QApplication application;
    MainWindow *window;
    TileMap *worldMap;
    Player *player;

    void initGame();

  public:
    Game(int argc, char *argv[]);

    int execGame();
};

#endif // GAME_H
