#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>

namespace gym
{

struct pos
{
    float x;
    float y;
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

} // namespace gym

#endif // STRUCTS_H
