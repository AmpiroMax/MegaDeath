#include "Game/game.h"

int main(int argc, char *argv[])
{
    Game game(argc, argv);
    game.initGame();
    return game.execGame();
}
