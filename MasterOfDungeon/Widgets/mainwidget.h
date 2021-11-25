#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "Game/gamewidget.h"
#include "Player/player.h"
#include "WorldMap/tilemap.h"

#include <QGridLayout>
#include <QObject>
#include <QWidget>

class MainWidget : public QWidget
{
  private:
    Q_OBJECT

    bool isGameStarted;

    GameWidget *gameWidget;
    QGridLayout *grid;

  public:
    explicit MainWidget(const TileMap *, Player *, QWidget *parent = nullptr);
    void startGame();

  private slots:
    virtual void showEvent(QShowEvent *) override;
};

#endif // MAINWIDGET_H
