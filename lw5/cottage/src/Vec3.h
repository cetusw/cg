#pragma once

#include <cmath>

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3 operator-(const Vec3 &other) const
    {
        return {
            x - other.x,
            y - other.y,
            z - other.z
        };
    }

    void Normalize()
    {
        const float length =
                std::sqrt(x * x + y * y + z * z);

        if (length == 0.0f)
        {
            return;
        }

        x /= length;
        y /= length;
        z /= length;
    }
};

inline Vec3 Cross(const Vec3 &a, const Vec3 &b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

inline Vec3 CalculateNormal(
    const Vec3 &a,
    const Vec3 &b,
    const Vec3 &c
)
{
    const Vec3 u = b - a;
    const Vec3 v = c - a;

    Vec3 normal = Cross(u, v);
    normal.Normalize();

    return normal;
}
