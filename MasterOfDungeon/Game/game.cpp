#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : app(argc, argv)
{
    player = new Player();
    gameWidget = new GameWidget();

    WM = new TileMap(":/maps/dungeon.txt");
    UM = new UnitMap(WM->shape());
    SM = new SpawnerMap(WM->shape());

    PLC = new PlayerController();
    EC = new EnemyController();
    SC = new SpawnerController();
    GC = new GraphicController();

    PLC->initParametrs(player, WM, UM);
    EC->initParametrs(UM, WM, player);
    SC->initParametrs(UM, SM, player);
    GC->initParametrs(gameWidget, WM, UM, player, PLC);

    app.setActiveWindow(gameWidget);
}

Game &Game::Instance(int argc, char *argv[])
{
    static Game game(argc, argv);
    return game;
}

void Game::initGame()
{
    SM->initializeSpawners(WM);

    // Соединяю сигнал таймера со слотом этого виджета.
    gameTimer.setInterval(15);
    connect(&gameTimer, &QTimer::timeout, this, &Game::timeOut);
}

int Game::execGame()
{
    // Запускаю таймер
    gameTimer.start();
    gameWidget->show();

    return app.exec();
}

void Game::timeOut()
{
    PLC->onTimeOutEvent();
    EC->onTimeOutEvent();
    SC->onTimeOutEvent();
    GC->onTimeOutEvent();
}
