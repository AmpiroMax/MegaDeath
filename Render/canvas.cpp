#include "canvas.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <string>

#include <QBuffer>
#include <QByteArray>
#include <QKeyEvent>
#include <QPixmap>

constexpr size_t tileSize = 32;  // 64 пикселя - ширина и сторона
constexpr size_t chunkSize = 16; // 16 тайликов - ширина и сторона

void Canvas::onInit()
{
    // Загрузка изображения из ресурсных файлов Qt
    // Довольно интересный момент в том плане, что
    // SFML не может загрузить изображение из ресурсов, как это делают QPixmap или QImage
    QPixmap pixmap(":/media/map.png"); // Но если создать объект QPixmap
    QByteArray bArray;                 // Создать объект массива байтов
    QBuffer buffer(&bArray);           // Поместить его в буфер
    buffer.open(QIODevice::WriteOnly); // Сохранить изображение в этот буфер, то есть в память
    pixmap.save(&buffer, "PNG");

    // А потом забрать сырые данные из буффера, с указанием количества забираемых данных
    canvasTexture.loadFromMemory(buffer.data().data(), buffer.data().size());
    // Эту процедуру понадобится произвести один раз при создании текстуры SFML

    // Далее устанавливаем изображения в sprite
    canvasSprite.setTexture(canvasTexture);
}

void Canvas::onUpdate()
{
    clear(clearColor);
    drawMap();
    this->setView(view);
}

void Canvas::drawMap()
{
    for (size_t i = 0; i < gameMap.landScape.size(); i++)
        for (size_t j = 0; j < gameMap.landScape[0].size(); j++)
        {
            if (gameMap.landScape[i][j] == '0')
                canvasSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
            if (gameMap.landScape[i][j] == 's')
                canvasSprite.setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
            if ((gameMap.landScape[i][j] == '1'))
                canvasSprite.setTextureRect(sf::IntRect(tileSize * 2, 0, tileSize, tileSize));

            canvasSprite.setPosition(j * tileSize, i * tileSize);
            draw(canvasSprite);
        }
}

QPaintEngine *Canvas::paintEngine() const
{
    // Возвращаем nullptr вместо движка отрисовки Qt, чтобы Qt не пытался что либо рисовать сам
    return nullptr;
}

void Canvas::showEvent(QShowEvent *)
{
    if (isInited)
        return;

    // Создём SFML окно для отрисовки.
    // Указываем системное Id окна, на котором будем рисовать
    RenderWindow::create(sf::WindowHandle(winId()));
    onInit();

    // Соединяем сигнал таймера со слотом перезапуска отрисовки виждета
    connect(&timer, &QTimer::timeout, this, &Canvas::onTimeout);
    timer.start();

    // Подключаю сигналы клавиатуры
    connect(&keyHandler, &KeyBoardHandler::quitKeyPressed, this, &Canvas::onCloseKey);
    connect(&keyHandler, &KeyBoardHandler::moveKeyPressed, this, &Canvas::onMoveKey);
    connect(&keyHandler, &KeyBoardHandler::zoomKeyPressed, this, &Canvas::onZoomKey);

    isInited = true;
    clearColor = sf::Color(100, 100, 100);
}

void Canvas::paintEvent(QPaintEvent *)
{
    onUpdate();
    display();
}

void Canvas::onTimeout()
{
    repaint();
}

void Canvas::onCloseKey()
{
    RenderWindow::close();
    emit closeWindow();
}

void Canvas::onMoveKey(int key)
{
    float dx = 3;
    float dy = 3;

    if (key == Qt::Key_A)
        view.move(-dx, 0);
    if (key == Qt::Key_W)
        view.move(0, -dy);
    if (key == Qt::Key_S)
        view.move(0, dy);
    if (key == Qt::Key_D)
        view.move(dx, 0);

    repaint();
}

void Canvas::onZoomKey(int key)
{
    if (key == Qt::Key_Z)
        view.zoom(0.9);
    else
        view.zoom(1.1);
    repaint();
}

Canvas::Canvas(QWidget *parent, uint frameTime)
    : QWidget(parent),
      sf::RenderWindow(sf::VideoMode(800, 600), "SFML|QT Canvas Test", sf::Style::Fullscreen, sf::ContextSettings(24)),
      gameMap(),
      keyHandler(this),
      isInited(false)
{
    // Атрибуты для отрисовки изображения на виджет
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    timer.setInterval(frameTime);
}
