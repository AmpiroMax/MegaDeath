#include "IUnit.h"

bool IUnit::isAinAreaOfB(GYM::fpos A, GYM::fpos B)
{
    // Функция проверяющая на достаточную близость два объекта A и B
    float epsilon = 4;

    if ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) < epsilon)
        return true;
    return false;
}

GYM::fpos IUnit::getUnitVector(GYM::fpos beg, GYM::fpos end)
{
    // Функция возвращает единичный вектор из точки beg в end

    float dx = end.x - beg.x;
    float dy = end.y - beg.y;
    float len = std::sqrt((beg.x - end.x) * (beg.x - end.x) + (beg.y - end.y) * (beg.y - end.y));

    return GYM::fpos(dx / len, dy / len);
}

void IUnit::changeTextureRect(int j)
{
    // переменная j отвечает за направление движения Unit
    // в зависимости отт неё выбирается один из 4 видов тайлов движения

    textureId.x = currentTextureTick / 5;
    textureId.y = j;

    // std::cout << textureId.y << std::endl;

    int xLeftTop = textureId.x * GYM::playerSpriteWidth;
    int yLefTtop = textureId.y * GYM::playerSpriteHight;

    sf::IntRect rect(xLeftTop, yLefTtop, GYM::playerSpriteWidth, GYM::playerSpriteHight);
    setTextureRect(rect);
}

int IUnit::getMovementId(float dx, float dy)
{
    // По навправлению движения юнита определяем какой индекст текстуры
    // необходимо применить на данный момент на юнита
    if (dx > 0)
    {
        if (dy == 0)
            return 4;
        if (dy < 0)
            return 3;
        if (dy > 0)
            return 5;
    }
    if (dx == 0)
    {
        if (dy < 0)
            return 2;
        if (dy > 0)
            return 6;
    }
    if (dx < 0)
    {
        if (dy == 0)
            return 0;
        if (dy < 0)
            return 1;
        if (dy > 0)
            return 7;
    }
    return -1;
}

IUnit::IUnit()
{
    textureId = GYM::ipos(0, 0);
    textureTick = 20;
    currentTextureTick = 0;
}

GYM::stats IUnit::getCharacteristics()
{
    return characteristics;
}

void IUnit::setCharacteristics(const GYM::stats &_characteristics)
{
    characteristics = _characteristics;
}

void IUnit::setPath(const CellVector &_path)
{
    // тут вроде должен конструктор копирования вызываться
    path = _path;
    path.pop_back();
}

void IUnit::setVelocity(const GYM::fpos &_velocity)
{
    velocity = _velocity;
}

void IUnit::moveUnit()
{
    // Функция перемещающая при каждом игровом такте юнита

    // если идти условно некуда, то стоим
    if (path.size() == 0)
        return;

    Cell nextCell = path.back();

    // координата центра следующего тайла,
    // а не просто координата его верхнего левого угла
    GYM::fpos nextCellPos(nextCell.first * GYM::tileSize + GYM::tileSize / 2,
                          nextCell.second * GYM::tileSize + GYM::tileSize / 2);

    // координата самого юнита
    GYM::fpos myPos(getPosition().x, getPosition().y);

    // двигаю персонажа, затем проверяю досиг ли он центра тайла
    // если нет, то ничего не делаю
    // если достиг, то выбрасываю этот тайл из пути

    GYM::fpos unitVector = getUnitVector(myPos, nextCellPos);
    float dx = velocity.x * unitVector.x;
    float dy = velocity.y * unitVector.y;

    if (!isAinAreaOfB(myPos, nextCellPos))
    {
        int j = getMovementId(dx, dy);
        changeTextureRect(j);
        if (currentTextureTick == textureTick)
        {
            currentTextureTick = 0;
        }
        currentTextureTick += 1;

        move(dx, dy);
        return;
    }
    path.pop_back();
    currentTextureTick = 0;
}
