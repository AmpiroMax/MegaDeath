#ifndef GAME_H
#define GAME_H

#include "gamewidget.h"
#include <QApplication>
#include <QWidget>

class Game
{
  private:
    QApplication application;
    GameWidget gameWidget;

  public:
    Game(int argc, char *argv[]);
};

#endif // GAME_H
