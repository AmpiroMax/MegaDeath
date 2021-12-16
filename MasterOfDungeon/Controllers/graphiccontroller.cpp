#include "graphiccontroller.h"

GraphicController::GraphicController()
{
}

void GraphicController::initParametrs(GameWidget *_gameWidget, const TileMap *_WM, const UnitMap *_UM,
                                      const Player *_player, PlayerController *_PLC)
{
    gameWidget = _gameWidget;
    WM = _WM;
    UM = _UM;
    player = _player;
    PLC = _PLC;

    connect(gameWidget, &GameWidget::paintEventSignal, this, &GraphicController::onPaintEvent);
    connect(gameWidget, &GameWidget::mouseEventSignal, this, &GraphicController::onMouseClickEvent);
    connect(gameWidget, &GameWidget::showEventSignal, this, &GraphicController::onShowEvent);
    connect(gameWidget, &GameWidget::resizeEventSignal, this, &GraphicController::onResizeEvent);
}

void GraphicController::onTimeOutEvent()
{
    paint();
}

void GraphicController::processMouseEvents(Cell mouseCell)
{
    PLC->recalculatePath(mouseCell);
}

#include <iostream>
using namespace std;

void GraphicController::paint()
{
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerPosition = {tmp.x, tmp.y};

    TileMatrix localWM = WM->getCentredLocalMap(playerPosition, 20, 20);
    UnitChunk localUM = UM->getLocalUnitMap(tmp);

    GYM::Point2D<size_t> shape = WM->shape();
    int horMapSize = localWM.size();
    int verMapSize = localWM[0].size();

    int deltaX =
        ((int(shape.x) - playerPosition.first > playerPosition.first) ? std::min(horMapSize / 2, playerPosition.first)
                                                                      : 20);
    int deltaY = ((int(shape.y) - playerPosition.second > playerPosition.second)
                      ? std::min(verMapSize / 2, playerPosition.second)
                      : 20);

    cout << "deltas " << deltaX << " " << deltaY << endl;

    int x0 = playerPosition.first - deltaX;
    int y0 = playerPosition.second - deltaY;

    Cell X0Y0(x0, y0);
    cout << "XoYo " << x0 << " " << y0 << endl;

    gameWidget->clear();
    gameWidget->setViewPosition(player->getPosition());
    gameWidget->drawMap(localWM, X0Y0);
    gameWidget->drawUnits(localUM);
    gameWidget->drawPlayer(player);
    gameWidget->display();
}

void GraphicController::onPaintEvent()
{
    paint();
}

void GraphicController::onMouseClickEvent(GYM::Point2D<int> pos)
{
    int width = gameWidget->size().width();
    int height = gameWidget->size().height();

    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerCell = {tmp.x, tmp.y};

    int xm = (pos.x - width / 2) / GYM::tileSize + playerCell.first;
    int ym = (pos.y - height / 2) / GYM::tileSize + playerCell.second;

    processMouseEvents(Cell(xm, ym));
}

void GraphicController::onShowEvent()
{
}

void GraphicController::onResizeEvent()
{
    int width = gameWidget->size().width();
    int height = gameWidget->size().height();
    // В случае изменения размера виджета, необходимо поменять
    // размер и SFML RenderWindow окну, для правильного отображения
    gameWidget->setSize(sf::Vector2u(width, height));
    // обновляю размеры камеры, для корректного отображения масштаба
    gameWidget->setViewSize(width, height);
}
