#include "gamewidget.h"
#include <math.h>

#include <QPainter>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent),
      sf::RenderWindow(sf::VideoMode(100, 60), "Widgets layout test", sf::Style::Default, sf::ContextSettings(24))

{
    // Отрибуты, необходимые для правильного отображения и использования
    // SFML в QWidget. Для чего необходимо каждое из них, написано в
    // документации Qt. Возможно в будующем я поясню для чего каждый
    // (всё написано в Qt документации)
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    QPixmap pixmap(":/media/textures/maptexture.png");
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    mapTexture.loadFromMemory(buffer.data().data(), buffer.data().size());
    canvasSprite.setTexture(mapTexture);

    // Создаю SFML окно, но не новое, а передаю контроль ему над
    // уже созданым QWidget, в котором и будет происходить отрисовка
    RenderWindow::create(sf::WindowHandle(winId()));
}

void GameWidget::drawMap(const TileMatrix &localMap, const Cell X0Y0)
{
    int horMapSize = localMap.size();
    int verMapSize = localMap[0].size();

    for (int i = 0; i < horMapSize; i++)
        for (int j = 0; j < verMapSize; j++)
        {
            if (localMap[i][j].isPassible())
            {
                canvasSprite.setTextureRect(
                    sf::IntRect(localMap[i][j].getTextureId() * GYM::tileSize, 0, GYM::tileSize, GYM::tileSize));
            }
            else
            {
                canvasSprite.setTextureRect(sf::IntRect(localMap[i][j].getTextureId() * GYM::tileSize, GYM::tileSize,
                                                        GYM::tileSize, GYM::tileSize));
            }

            canvasSprite.setPosition((i + X0Y0.first) * GYM::tileSize, (j + X0Y0.second) * GYM::tileSize);
            draw(canvasSprite);
        }
}

void GameWidget::drawUnits(const UnitChunk &localUnits)
{
    for (auto unit : localUnits)
    {
        draw(*unit.first);
    }
}

void GameWidget::drawPlayer(const Player *player)
{
    draw(*player);
}

void GameWidget::setViewPosition(sf::Vector2f newViewPos)
{
    view.setCenter(newViewPos);
    setView(view);
}

void GameWidget::setViewSize(int width, int height)
{
    view.setSize(size().width(), size().height());
}

void GameWidget::setViewZoom(float zoomFactor)
{
    view.zoom(zoomFactor);
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
    emit paintEventSignal();
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    emit keyPressEventSignal(event->key());
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
    GYM::Point2D<int> pos(event->pos().x(), event->pos().y());
    emit mouseEventSignal(pos);
}

void GameWidget::showEvent(QShowEvent *)
{
    emit showEventSignal();
}

void GameWidget::resizeEvent(QResizeEvent *)
{
    emit resizeEventSignal();
}
