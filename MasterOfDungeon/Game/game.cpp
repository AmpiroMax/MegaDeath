#include "game.h"

Game::Game(int argc, char *argv[]) : application(argc, argv), worldMap(":/maps/hut.txt")
{
    gameWidget.setWorldMap(&worldMap);
    gameWidget.show();
}

int Game::gameLoop()
{

    return application.exec();
}
