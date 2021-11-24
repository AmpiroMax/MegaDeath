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
    timer.setInterval(20);
    clearColor = sf::Color(100, 0, 0);
}

void GameWidget::initMapPlayer(const TileMap *map, const Player *_player)
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
    TileMatrix mapMatrix;

    for (size_t i = 0; i < mapMatrix.size(); i++)
        for (size_t j = 0; j < mapMatrix[0].size(); j++)
        {
            if (mapMatrix[i][j].isPassible())
                canvasSprite.setTextureRect(sf::IntRect(0, 0, GYM::tileSize, GYM::tileSize));
            else
                canvasSprite.setTextureRect(sf::IntRect(GYM::tileSize, 0, GYM::tileSize, GYM::tileSize));

            canvasSprite.setPosition(j * GYM::tileSize, i * GYM::tileSize);
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
    // drawMap();
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

void GameWidget::onTimeout()
{
    // repaint();
}
