#include "gamewidget.h"
#include <math.h>

#include <QPainter>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent),
      sf::RenderWindow(sf::VideoMode(0, 0), "Widgets layout test", sf::Style::Default, sf::ContextSettings(24))

{
    // Отрибуты, необходимые для правильного отображения и использования
    // SFML в QWidget. Для чего необходимо каждое из них, написано в
    // документации Qt. Возможно в будующем я поясню для чего каждый
    // (всё написано в F1)
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    isInited = false;
    timer.setInterval(15);
    clearColor = sf::Color(100, 0, 0);
}

void GameWidget::initMapPlayer(const TileMap *map, Player *_player)
{
    worldMap = map;
    player = _player;

    QPixmap pixmap(":/media/textures/maptexture.png");
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    mapTexture.loadFromMemory(buffer.data().data(), buffer.data().size());
    canvasSprite.setTexture(mapTexture);
}

void GameWidget::drawMap()
{
    TileMatrix mapMatrix = worldMap->getCentredLocalMap({10, 10}, 50, 50);

    for (size_t i = 0; i < mapMatrix.size(); i++)
        for (size_t j = 0; j < mapMatrix[0].size(); j++)
        {
            if (mapMatrix[i][j].isPassible())
            {
                canvasSprite.setTextureRect(
                    sf::IntRect(mapMatrix[i][j].getTextureId() * GYM::tileSize, 0, GYM::tileSize, GYM::tileSize));
            }
            else
            {
                canvasSprite.setTextureRect(sf::IntRect(mapMatrix[i][j].getTextureId() * GYM::tileSize, GYM::tileSize,
                                                        GYM::tileSize, GYM::tileSize));
            }

            canvasSprite.setPosition(i * GYM::tileSize, j * GYM::tileSize);
            draw(canvasSprite);
        }
}

QPaintEngine *GameWidget::paintEngine() const
{
    // В силу того, что мы рисуем в окне через SFML, были установлены
    // определенные отрибуты. Один из них требует установить возвращаемым
    // значением в данной функции nullptr, чтобы в случае, если кто-то захочет
    // что-то рисовать через Qt, у него это не получччилось, т.к. такой
    // возможности здесь неподразумевается
    return nullptr;
}

void GameWidget::paintEvent(QPaintEvent *)
{
    if (!isInited)
        return;

    clear(clearColor);
    view.setCenter(player->getPosition());
    setView(view);
    drawMap();
    draw(*player);
    display();
}

void GameWidget::showEvent(QShowEvent *)
{
    // Проделываем данные операции только один раз,
    // когда наше окно было впервые отображено на экране
    if (isInited)
        return;

    // Создаю SFML окно, но не новое, а передаю контроль ему над
    // уже созданым QWidget, в котором и будет происходить отрисовка
    RenderWindow::create(sf::WindowHandle(winId()));

    // Изначальные настройки положения камеры
    view.setCenter(player->getPosition());
    view.setSize(size().width(), size().height());

    // Соединяю сигнал таймера со слотом этого виджета.
    // Запускаю таймер
    connect(&timer, &QTimer::timeout, this, &GameWidget::onTimeout);
    timer.start();

    isInited = true;
}

void GameWidget::resizeEvent(QResizeEvent *)
{
    // В случае изменения размера виджета, необходимо поменять
    // размер и SFML RenderWindow окну, для правильного отображения
    setSize(sf::Vector2u(size().width(), size().height()));
    // обновляю размеры камеры, для корректного отображения масштаба
    view.setSize(size().width(), size().height());
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
    GYM::ipos pos(event->pos().x(), event->pos().y());

    if (event->button() == Qt::MouseButton::RightButton)
        movePlayer(pos);
}

#include <iostream>

void GameWidget::movePlayer(GYM::ipos pos)
{
    // Это такая хуета что я в ахуе сижу, пока пишу
    // перед всем - важная информация:
    // координаты мышки я получаю в системе отсчета виджета
    // координата игрока - в системее отсчета sfml карты

    //    std::cout << "size/2   " << size().width() / 2 << " " << size().height() / 2 << std::endl;
    //    std::cout << "pos      " << pos.x << " " << pos.y << std::endl;
    //    std::cout << "player   " << player->getPosition().x << " " << player->getPosition().x << std::endl;

    int xp = int(player->getPosition().x);
    int yp = int(player->getPosition().y);

    int xm = pos.x;
    int ym = pos.y;

    xm -= size().width() / 2;
    ym -= size().height() / 2;

    xm += xp;
    ym += yp;

    xm /= GYM::tileSize;
    ym /= GYM::tileSize;

    xp /= GYM::tileSize;
    yp /= GYM::tileSize;

    //    std::cout << "----------------" << std::endl;
    //    std::cout << "xp, yp " << xp << " " << yp << std::endl;
    //    std::cout << "xm, ym " << xm << " " << ym << std::endl;

    Cell playerCell(xp, yp);
    Cell mouseCell(xm, ym);

    CellVector newPath = worldMap->getShortestWay(playerCell, mouseCell);
    std::reverse(newPath.begin(), newPath.end());
    player->setPath(newPath);

    //    std::cout << "----------------------printting path" << std::endl;
    //    std::cout << "path size " << newPath.size() << std::endl;
    //    for (auto cell : newPath)
    //    {
    //        std::cout << cell.first << " " << cell.second << ", ";
    //    }
    //    std::cout << std::endl;
    //    std::cout << "----------------------end of printing " << std::endl;
}

void GameWidget::onTimeout()
{
    player->moveUnit();
    repaint();
}
