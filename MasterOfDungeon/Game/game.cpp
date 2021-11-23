#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : application(argc, argv)
{
    player = new Player();
    worldMap = new TileMap(":/maps/massive_stone.txt");
    gameWidget = new GameWidget;

    application.setActiveWindow(gameWidget);
    gameWidget->initMapPlayer(worldMap, player);

    initGame();
}

void Game::initGame()
{
    gameWidget->show();
}

int Game::execGame()
{
    return application.exec();
}
