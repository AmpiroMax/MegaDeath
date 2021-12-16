#ifndef GAME_H
#define GAME_H

#include "Game/gamewidget.h"
#include "Player/player.h"
#include "UnitMap/unit_map.h"
#include "WorldMap/tilemap.h"

#include "Controllers/graphiccontroller.h"
#include "Controllers/playercontroller.h"

#include <QApplication>
#include <QTimer>
#include <QWidget>

class Game : public QObject
{
    Q_OBJECT
  private:
    Player *player;
    GameWidget *gameWidget;
    TileMap *WM;
    UnitMap *UM;

    PlayerController *PLC;
    GraphicController *GC;

    QTimer gameTimer;
    QApplication app;

  public:
    Game(int argc, char *argv[]);
    void initGame();
    int execGame();

  private slots:
    void timeOut();
};

#endif // GAME_H
