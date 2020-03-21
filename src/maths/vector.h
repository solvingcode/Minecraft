#pragma once

#include <vector>

struct VectorXY
{
    float x, y;
};

struct Vector3i
{
    int x, y, z;
    Vector3i(int x_, int y_, int z_) : x(x_), y(y_), z(z_)
    {
    }
    bool operator==(const Vector3i &v) const
    {
        return v.x == x && v.y == y && v.z == z;
    }
};

struct Vector2i
{
    int x, z;
    Vector2i(int x_, int z_) : x(x_), z(z_)
    {
    }
    bool operator==(const Vector2i &v) const noexcept
    {
        return v.x == x && v.z == z;
    }
};

namespace std
{
template <>
struct hash<class Vector2i>
{
    std::size_t operator()(const Vector2i &v) const
    {
        std::size_t h1 = std::hash<int>()(v.x);
        std::size_t h2 = std::hash<int>()(v.z);

        return hash<decltype(v.x)>{}((h1 ^ h2) >> 2);
    }
};

template <>
struct hash<class Vector3i>
{
    std::size_t operator()(const Vector3i &node) const
    {
        std::size_t h1 = std::hash<int>()(node.x);
        std::size_t h2 = std::hash<int>()(node.y);
        std::size_t h3 = std::hash<int>()(node.z);

        return h1 ^ h2 ^ h3;
    }
};
}; // namespace std