#pragma once

#include "pch.h"

struct Vec4 {
    float r, g, b, a;
};

const double pi = 3.14159265358979323846;

class vec3
{
public:

    union
    {
        struct { float x, y, z; };
        float v[3];
    };

    vec3() { x = y = z = 0; }
    vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    vec3 operator + (const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    vec3 operator - (const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    vec3 operator * (const float& rhs) const { return vec3(x * rhs, y * rhs, z * rhs); }
    vec3 operator / (const float& rhs) const { return vec3(x / rhs, y / rhs, z / rhs); }
    vec3& operator += (const vec3& rhs) { return *this = *this + rhs; }
    vec3& operator -= (const vec3& rhs) { return *this = *this - rhs; }
    vec3& operator *= (const float& rhs) { return *this = *this * rhs; }
    vec3& operator /= (const float& rhs) { return *this = *this / rhs; }
    float dot() const { return x * x + y * y + z * z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float Distance(const vec3& rhs) const { return static_cast<float>((*this - rhs).Length() * 0.0254); }
    void Normalize() {
        while (y < -180) { y += 360; }
        while (y > 180) { y -= 360; }
        if (x > 89) { x = 89; }
        if (x < -89) { x = -89; }
    }
};

