#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : application(argc, argv)
{
    player = new Player();
    worldMap = new TileMap(":/maps/massive_map.txt");
    gameWidget = new GameWidget();

    application.setActiveWindow(gameWidget);
    gameWidget->initMapPlayer(worldMap, player);

    initGame();
}

void Game::initGame()
{
    player->setPosition(GYM::tileSize * 13.5, GYM::tileSize * 13.5);
    player->setVelocity(GYM::fpos(4, 4));
    gameWidget->show();
}

int Game::execGame()
{
    return application.exec();
}
