#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>

namespace GYM
{

constexpr int playerSpriteWidth = 32;
constexpr int playerSpriteHight = 64;

struct fpos
{
    float x;
    float y;
};

struct ipos
{
    int x;
    int y;
};

struct uipos
{
    size_t x;
    size_t y;
};

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
