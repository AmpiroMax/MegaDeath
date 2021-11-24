#include "player.h"

#include <QBuffer>
#include <QByteArray>
#include <QPixmap>

Player::Player()
{
    // Загрузка изображения из ресурсных файлов Qt
    // Довольно интересный момент в том плане, что
    // SFML не может загрузить изображение из ресурсов, как это делают QPixmap или QImage

    QPixmap pixmap(":/media/unitsTextures/player/demo1.png"); // Но если создать объект QPixmap

    QByteArray bArray;       // Создать объект массива байтов
    QBuffer buffer(&bArray); // Поместить его в буфер

    buffer.open(QIODevice::WriteOnly); // Сохранить изображение в этот буфер, то есть в память

    pixmap.save(&buffer, "PNG");

    // Загружаю текстуру в своего юнита
    unitTexture.loadFromMemory(buffer.data().data(), buffer.data().size());
    // Устанавливаю текстуру у Shape
    setTexture(&unitTexture);
    // Устанавливаю начальное положение отрисовываемой части текстуры
    sf::IntRect rect(0, 0, GYM::playerSpriteWidth, GYM::playerSpriteHight);
    setTextureRect(rect);

    sf::Vector2f size(GYM::playerSpriteWidth, GYM::playerSpriteHight);
    setSize(size);

    setOrigin(GYM::playerSpriteWidth / 2, GYM::playerSpriteHight / 2);
}
