#ifndef GAME_H
#define GAME_H

#include "Game/gamewidget.h"
#include "Player/player.h"
#include "SpawnerMap/spawnermap.h"
#include "UnitMap/unit_map.h"
#include "WorldMap/tilemap.h"

#include "Controllers/enemycontroller.h"
#include "Controllers/graphiccontroller.h"
#include "Controllers/playercontroller.h"
#include "Controllers/spawnercontroller.h"

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
    SpawnerMap *SM;

    PlayerController *PLC;
    EnemyController *EC;
    SpawnerController *SC;
    GraphicController *GC;

    QTimer gameTimer;
    QApplication app;

    Game(int argc, char *argv[]);
    Game(Game const &) = delete;
    Game &operator=(Game const &) = delete;

  public:
    static Game &Instance(int argc, char *argv[]);

    void initGame();
    int execGame();

  private slots:
    void timeOut();
};

#endif // GAME_H
