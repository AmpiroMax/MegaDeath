#include "Game/game.h"

int main(int argc, char *argv[])
{
    // Класс game - singltone, поэтому мы создаем его не обычным конструктором,
    // а через получение сущности данного класса
    Game &game = Game::Instance(argc, argv);
    game.initGame();
    return game.execGame();
}
