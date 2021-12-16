#include "mainwidget.h"

MainWidget::MainWidget(const TileMap *tileMap, Player *player, QWidget *parent) : QWidget(parent)
{
    gameWidget = new GameWidget(this);
    // gameWidget->initMapPlayer(tileMap, player);

    grid = new QGridLayout(this);
    grid->addWidget(gameWidget);
    grid->setContentsMargins(0, 0, 0, 0);
    setLayout(grid);

    isGameStarted = false;
}

void MainWidget::startGame()
{
    isGameStarted = true;
    show();
}

void MainWidget::showEvent(QShowEvent *)
{
    if (isGameStarted)
        show();
    return;
}
