#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
#include <fstream>

namespace GYM
{

constexpr int tileSize = 32;
constexpr int chunkSize = 16;
constexpr int playerSpriteWidth = 32;
constexpr int playerSpriteHight = 64;

struct fpos
{
    float x;
    float y;

    fpos()
    {
        x = 0;
        y = 0;
    }

    fpos(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

struct ipos
{
    int x;
    int y;

    ipos()
    {
        x = 0;
        y = 0;
    }

    ipos(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

struct uipos
{
    size_t x;
    size_t y;
};

template <typename Type>
struct Point2D
{
    explicit Point2D();
    explicit Point2D(Type _x, Type _y);

    Type x;
    Type y;

    friend bool operator== (const Point2D<Type>& lhs, const Point2D<Type>& rhs);
    friend std::ostream& operator<< (std::ostream& output, const Point2D<Type>& point);
};

template <typename Type>
Point2D<Type>::Point2D(Type _x, Type _y): x(_x), y(_y) {}

template <typename Type>
Point2D<Type>::Point2D(): Point2D(0, 0) {}

template <typename Type>
bool operator== (const Point2D<Type>& lhs, const Point2D<Type>& rhs)
{
    if ((lhs.x == rhs.x) && (lhs.y == rhs.y))
        return true;

    return false;
}

template <typename Type>
std::ostream& operator<< (std::ostream& output, const Point2D<Type>& point)
{
    output << "x, y = " << point.x << ", " << point.y;
}

struct stats
{
    float health;
    float mana;
    float strength;
    float agility;
    float intelligence;
};

struct inventory
{
    std::vector<size_t> objects;
};

} // namespace GYM

#endif // STRUCTS_H
