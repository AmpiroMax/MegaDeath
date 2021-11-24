#include "IUnit.h"

bool IUnit::isAinAreaOfB(GYM::fpos A, GYM::fpos B)
{
    float epsilon = 4;

    if ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) < epsilon)
        return true;
    return false;
}

// Функция возвращает единичный вектор из точки beg в end
GYM::fpos IUnit::getUnitVector(GYM::fpos beg, GYM::fpos end)
{
    float dx = end.x - beg.x;
    float dy = end.y - beg.y;
    float len = std::sqrt((beg.x - end.x) * (beg.x - end.x) + (beg.y - end.y) * (beg.y - end.y));

    return GYM::fpos(dx / len, dy / len);
}

IUnit::IUnit()
{
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

    //    std::cout << "dx, dy      " << dx << ", " << dy << std::endl;
    //    std::cout << "myPos       " << myPos.x << ", " << myPos.y << std::endl;
    //    std::cout << "nextCellPos " << nextCellPos.x << ", " << nextCellPos.y << std::endl;

    if (!isAinAreaOfB(myPos, nextCellPos))
    {
        move(dx, dy);
        return;
    }
    path.pop_back();
}
