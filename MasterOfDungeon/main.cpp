#include "Game/game.h"

int main(int argc, char *argv[])
{
    Game game(argc, argv);
    game.gameLoop();
    return 0;
}
