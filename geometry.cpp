//
// Created by eugene on 29.06.15.
//

#include "geometry.h"

Vec2i::Vec2i(const Vec2f &v) {
    this->x = v.x;
    this->y = v.y;
}

Vec2i& Vec2i::operator=(const Vec2f &v) {
        x = v.x;
        y = v.y;
        return *this;
}

Vec2f Vec2i::operator*(float f) const { return Vec2f(x*f, y*f);}

Vec2f Vec2i::normalize(float f)  {
    Vec2f v(x, y);
    v = v * (f / v.norm());
    return v;
}

Vec3f& Vec3f::operator=(const Vec3i &v)  {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3f Vec3f::operator+(const Vec3i &v) const {return Vec3f(x+v.x, y+v.y,z + v.z);}

Vec3f Vec3f::operator-(const Vec3i &v) const  {return Vec3f(x-v.x, y-v.y,z - v.z);}

float Vec3f::operator*(const Vec3i &v) const  { return x * v.x + y*v.y + z * v.z;}

Vec3f Vec3f::operator^(const Vec3i &v) const  {
    return Vec3f(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
}

