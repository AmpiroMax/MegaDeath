#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : application(argc, argv)
{
    player = new Player();
    worldMap = new TileMap(":/maps/massive_map.txt");
    window = new MainWindow();

    window->initGameWidget(worldMap, player);

    application.setActiveWindow(window);
    initGame();
}

void Game::initGame()
{
    player->setPosition(GYM::tileSize * 13.5, GYM::tileSize * 13.5);
    player->setVelocity(GYM::fpos(4, 4));
}

int Game::execGame()
{
    window->show();
    return application.exec();
}
