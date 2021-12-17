#include "game.h"

#include <QThread>

Game::Game(int argc, char *argv[]) : app(argc, argv)
{
    // Создаём все игровые объекты: карты, спавнеры, игрока, игровой виджет
    player = new Player();
    gameWidget = new GameWidget();

    WM = new TileMap(":/maps/dungeon.txt");
    UM = new UnitMap(WM->shape());
    SM = new SpawnerMap(WM->shape());

    PLC = new PlayerController();
    EC = new EnemyController();
    SC = new SpawnerController();
    GC = new GraphicController();

    // Инициализируем параметры контроллеров
    PLC->initParametrs(player, WM, UM);
    EC->initParametrs(UM, WM, player);
    SC->initParametrs(UM, SM, player);
    GC->initParametrs(gameWidget, WM, UM, player, PLC);

    // Устанавливаем в Qt приложении главным виджетом наш игровой виджет
    app.setActiveWindow(gameWidget);
}

Game &Game::Instance(int argc, char *argv[])
{
    // Так как Game - singltone создавать его обычным конструктором нельзя
    // для этого возвращаем указатель на сущность класса game
    static Game game(argc, argv);
    return game;
}

void Game::initGame()
{
    // Инициализируем спавнеры
    SM->initializeSpawners(WM);

    // Соединяю сигнал таймера со слотом этого виджета.
    gameTimer.setInterval(15);
    connect(&gameTimer, &QTimer::timeout, this, &Game::timeOut);
}

int Game::execGame()
{
    // Запускаю таймер
    gameTimer.start();
    // Отображаю gameWidget на экран
    gameWidget->show();

    // Запускаем внутри Qt цикл обработки событий
    return app.exec();
}

void Game::timeOut()
{
    // При срабатывании сигнала от таймера сообщаем всем контроллерам
    // провести необходимые изменения в подконтрольных им объектам
    PLC->onTimeOutEvent();
    EC->onTimeOutEvent();
    SC->onTimeOutEvent();
    GC->onTimeOutEvent();
}
