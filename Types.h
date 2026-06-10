#pragma once
#include <vector>

struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

enum class ObjectType
{
    Gear,
    StaticObject
};

struct ObjData
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    Vec3 center = { 0.0f, 0.0f, 0.0f };
};
