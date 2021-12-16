#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : app(argc, argv)
{
    player = new Player();
    gameWidget = new GameWidget();

    WM = new TileMap(":/maps/massive_map.txt");
    UM = new UnitMap(WM->shape());

    PLC = new PlayerController();
    GC = new GraphicController();

    GC->initParametrs(gameWidget, WM, UM, player, PLC);
    PLC->initParametrs(player, WM, UM);
    app.setActiveWindow(gameWidget);

    // Соединяю сигнал таймера со слотом этого виджета.
    gameTimer.setInterval(15);
    connect(&gameTimer, &QTimer::timeout, this, &Game::timeOut);
}

void Game::initGame()
{
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
    GC->onTimeOutEvent();
    PLC->onTimeOutEvent();
}
