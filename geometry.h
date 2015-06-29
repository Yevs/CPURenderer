//
// Created by eugene on 24.06.15.
//

#ifndef CPURENDERER_GEOMETRY_H
#define CPURENDERER_GEOMETRY_H


#include <cmath>
#include <ostream>
#include <iostream>

using namespace std;

struct Vec2f;

struct Vec2i {
    int x, y;
    Vec2i() {}
    Vec2i(int _x, int _y) : x(_x), y(_y) {}
    Vec2i(const Vec2i &v) {*this = v;}

    Vec2i(const Vec2f &v);

    Vec2i & operator =(const Vec2f &v);

    Vec2i & operator =(const Vec2i &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
        }
        return *this;
    }
    Vec2i operator +(const Vec2i &v) const {return Vec2i(x+v.x, y+v.y);}
    Vec2f operator *(float f) const;
    Vec2i operator -(const Vec2i &v) const {return Vec2i(x - v.x, y - v.y);}
    int operator *(const Vec2i &v) const { return x * v.x + y*v.y;}
    int operator ^(const Vec2i &v) const { return x * v.y - y * v.x;}

    float norm() {return sqrt(x*x + y*y);}
    Vec2f normalize(float f = 1);
    friend ostream& operator<< (ostream &out, Vec2i &v) {
        out << "(" << v.x << ", " << v.y << ")\n";
        return out;
    }
};

struct Vec2f {
    float x, y;
    Vec2f() {}
    Vec2f(float _x, float _y): x(_x), y(_y) {}
    Vec2f (const Vec2f &v) {*this = v;}

    Vec2f & operator =(const Vec2f &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
        }
        return *this;
    }

    Vec2f & operator =(const Vec2i &v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vec2f operator +(const Vec2f &v) const {return Vec2f(x+v.x, y+v.y);}
    Vec2f operator *(float f) const {return Vec2f(x*f, y*f);}
    Vec2f operator -(const Vec2f &v) const {return *this+(v*(-1));}
    float operator *(const Vec2f &v) const { return x * v.x + y*v.y;}
    float operator ^(const Vec2f &v) const { return x * v.y - y * v.x;}

    Vec2f operator +(const Vec2i &v) const {return Vec2f(x+v.x, y+v.y);}
    Vec2f operator -(const Vec2i &v) const {return *this+(v*(-1));}
    float operator *(const Vec2i &v) const { return x * v.x + y*v.y;}
    float operator ^(const Vec2i &v) const { return x * v.y - y * v.x;}

    float norm() {return sqrt(x*x + y*y);}
    void normalize(float f = 1) {*this = *this * (f/norm());}

    friend ostream& operator<< (ostream &out, Vec2f &v) {
        out << "(" << v.x << ", " << v.y << ")\n";
        return out;
    }
};

struct Vec3i;

struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
    Vec3f (const Vec3f &v) {*this = v;}

    Vec3f & operator =(const Vec3f &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    Vec3f & operator =(const Vec3i &v);

    Vec3f operator +(const Vec3f &v) const {return Vec3f(x+v.x, y+v.y, z+v.z);}
    Vec3f operator *(float f) const {return Vec3f(x*f, y*f, z*f);}
    Vec3f operator -(const Vec3f &v) const {return *this+(v*(-1));}
    float operator *(const Vec3f &v) const { return x * v.x + y*v.y + z*v.z;}
    Vec3f operator ^(const Vec3f &v) const {
        return Vec3f(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
    }

    Vec3f operator +(const Vec3i &v) const;
    Vec3f operator -(const Vec3i &v) const;
    float operator *(const Vec3i &v) const;
    Vec3f operator ^(const Vec3i &v) const;

    float norm() {return sqrt(x*x + y*y+z*z);}
    void normalize(float f = 1) {*this = *this * (f/norm());}

    friend ostream& operator<< (ostream &out, Vec3f &v) {
        out << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return out;
    }
};

struct Vec3i {
    int x, y, z;

    Vec3i() {}
    Vec3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    Vec3i(const Vec3i &v) {*this = v;}

    Vec3i(const Vec3f &v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    Vec3i & operator =(const Vec3f &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vec3i & operator =(const Vec3i &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }
    Vec3i operator +(const Vec3i &v) const {return Vec3i(x+v.x, y+v.y, z+v.z);}
    Vec3f operator *(float f) const {return Vec3f(x*f, y*f, z*f);}
    Vec3i operator -(const Vec3i &v) const {return *this+(v*(-1));}
    int operator *(const Vec3i &v) const { return x * v.x + y*v.y + z*v.z;}
    Vec3i operator ^(const Vec3i &v) const {
        return Vec3i(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
    }

    float norm() {return sqrt(x*x + y*y+z*z);}
    Vec3f normalize(float f = 1) {
        Vec3f v(x, y, z);
        v = v * (f / v.norm());
        return v;
    }

    friend ostream& operator<< (ostream &out, Vec3i &v) {
        out << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return out;
    }
};

//template <class t> struct Vec2 {
//    t x, y;
//    Vec2<t>() : x(t()), y(t()) {}
//    Vec2<t>(t _x, t _y) : x(_x), y(_y) {}
//    Vec2<t>(const Vec2<t> &v) : x(t()), y(t()) { *this = v; }
//    Vec2<t> & operator =(const Vec2<t> &v) {
//        if (this != &v) {
//            x = v.x;
//            y = v.y;
//        }
//        return *this;
//    }
//    Vec2<t> operator +(const Vec2<t> &V) const { return Vec2<t>(x+V.x, y+V.y); }
//    Vec2<t> operator -(const Vec2<t> &V) const { return Vec2<t>(x-V.x, y-V.y); }
//    Vec2<t> operator *(float f) const { return Vec2<t>(x*f, y*f); }
//    t& operator[](const int i) { if (x<=0) return x; else return y; }
//};
//template <class t> struct Vec3 {
//    t x, y, z;
//    Vec3<t>() : x(t()), y(t()), z(t()) { }
//    Vec3<t>(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}
//    template <class u> Vec3<t>(const Vec3<u> &v);
//    Vec3<t>(const Vec3<t> &v) : x(t()), y(t()), z(t()) { *this = v; }
//    Vec3<t> & operator =(const Vec3<t> &v) {
//        if (this != &v) {
//            x = v.x;
//            y = v.y;
//            z = v.z;
//        }
//        return *this;
//    }
//    Vec3<t> operator ^(const Vec3<t> &v) const { return Vec3<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
//    Vec3<t> operator +(const Vec3<t> &v) const { return Vec3<t>(x+v.x, y+v.y, z+v.z); }
//    Vec3<t> operator -(const Vec3<t> &v) const { return Vec3<t>(x-v.x, y-v.y, z-v.z); }
//    Vec3<t> operator *(float f) const { return Vec3<t>(x*f, y*f, z*f); }
//    t operator *(const Vec3<t> &v) const { return x*v.x + y*v.y + z*v.z; }
//    float norm () const { return std::sqrt(x*x+y*y+z*z); }
//    Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
//    t& operator[](const int i) { if (i<=0) return x; else if (i==1) return y; else return z; }
//    template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<t>& v);
//};
//typedef Vec2<float> Vec3f;
//typedef Vec2<int> Vec3i;
//typedef Vec3<float> Vec3f;
//typedef Vec3<int> Vec3i;


#endif //CPURENDERER_GEOMETRY_H