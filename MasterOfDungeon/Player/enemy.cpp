#include "enemy.h"

Enemy::Enemy()
{
}

void Enemy::setEnemyTexture(QString textureName)
{
    // Загрузка изображения из ресурсных файлов Qt
    // Довольно интересный момент в том плане, что
    // SFML не может загрузить изображение из ресурсов, как это делают QPixmap или QImage

    QPixmap pixmap(textureName); // Но если создать объект QPixmap

    QByteArray bArray;       // Создать объект массива байтов
    QBuffer buffer(&bArray); // Поместить его в буфер

    buffer.open(QIODevice::WriteOnly); // Сохранить изображение в этот буфер, то есть в память

    pixmap.save(&buffer, "PNG");

    // Загружаю текстуру в своего юнита
    unitTexture.loadFromMemory(buffer.data().data(), buffer.data().size());
    // Устанавливаю текстуру у Shape
    setTexture(&unitTexture);

    // Устанавливаю начальное положение отрисовываемой части текстуры
    int xLeftTop = textureId.x * GYM::playerSpriteWidth;
    int yLefTtop = textureId.y * GYM::playerSpriteHight;

    sf::IntRect rect(xLeftTop, yLefTtop, GYM::playerSpriteWidth, GYM::playerSpriteHight);
    setTextureRect(rect);

    sf::Vector2f size(GYM::playerSpriteWidth, GYM::playerSpriteHight);
    setSize(size);

    setOrigin(GYM::playerSpriteWidth / 2, GYM::playerSpriteHight);
}

void Enemy::updateLogicState(const Cell &pp)
{
    Point2D<int> myPos = getUnitTilePos(this);
    if ((pp.first - myPos.x) * (pp.first - myPos.x) + (pp.second - myPos.y) * (pp.second - myPos.y) < 7 * 7)
        logicState = 1;
    else
        logicState = 0;
}

int Enemy::getLogicState()
{
    return logicState;
}
