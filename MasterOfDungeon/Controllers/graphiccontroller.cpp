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
    connect(gameWidget, &GameWidget::keyPressEventSignal, this, &GraphicController::onKeyPressEvent);
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

void GraphicController::processKeyboardEvents(int code)
{
    switch (code)
    {
        case Qt::Key_Z:
        {
            gameWidget->setViewZoom(1.1);
            break;
        }
        case Qt::Key_X:
        {
            gameWidget->setViewZoom(0.9);
            break;
        }
    }
}

Cell GraphicController::calculateMarginForMap(const TileMatrix &localMap, int marginSize)
{
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerPosition = {tmp.x, tmp.y};

    GYM::Point2D<int> shape(WM->shape().x, WM->shape().y);
    int horMapSize = localMap.size();
    int verMapSize = localMap[0].size();

    int deltaX = 0;
    int deltaY = 0;

    if (shape.x - playerPosition.first > marginSize)
        deltaX = std::min(horMapSize / 2, playerPosition.first);
    else
        deltaX = horMapSize - shape.x + playerPosition.first;

    if (shape.y - playerPosition.second > marginSize)
        deltaY = std::min(verMapSize / 2, playerPosition.second);
    else
        deltaY = verMapSize - shape.y + playerPosition.second;

    return Cell(playerPosition.first - deltaX, playerPosition.second - deltaY);
}

void GraphicController::paint()
{
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerPosition = {tmp.x, tmp.y};

    TileMatrix localWM = WM->getCentredLocalMap(playerPosition, 100, 100);
    GYM::Point2D<int> playerChunk = getUnitChunkPos(player);
    UnitChunk localUM = UM->getLocalUnitMap(playerChunk);

    Cell X0Y0 = calculateMarginForMap(localWM, 100);

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

void GraphicController::onKeyPressEvent(int code)
{
    processKeyboardEvents(code);
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
