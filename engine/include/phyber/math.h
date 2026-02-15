#ifndef PHYBER_ENGINE_PHY_MATH_H
#define PHYBER_ENGINE_PHY_MATH_H

#include <stdexcept>
#include <stdint.h>
#include <stddef.h>

namespace Phyber {

class Vec2Int;
class Vec2 {
public:
    float x = 0, y = 0;
    Vec2() {}
    Vec2(const Vec2 &v) = default;
    Vec2(Vec2 &&v) = default;
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(const Vec2Int &v);

    float &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else throw std::runtime_error("Out of bounds"); }
    float operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else throw std::runtime_error("Out of bounds"); }

    Vec2 &operator=(const Vec2 &v);
    Vec2 &operator=(const Vec2Int &v);
    bool operator==(const Vec2 &v) const;
    Vec2 operator-() const;
    Vec2 operator+(const Vec2 &v) const;
    Vec2 operator-(const Vec2 &v) const;
    float operator*(const Vec2 &v) const;
    Vec2 operator*(float scalar) const;
    Vec2 &operator+=(const Vec2 &v);
    Vec2 &operator-=(const Vec2 &v);
    Vec2 &operator*=(float scalar);

    float length() const;
};

class Vec3Int;
class Vec3 {
public:
    float x = 0, y = 0, z = 0;
    Vec3() {}
    Vec3(const Vec3 &v) = default;
    Vec3(Vec3 &&v) = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const Vec3Int &v);

    float &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else throw std::runtime_error("Out of bounds"); }
    float operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else throw std::runtime_error("Out of bounds"); }

    Vec3 &operator=(const Vec3 &v);
    Vec3 &operator=(const Vec3Int &v);
    bool operator==(const Vec3 &v) const;
    Vec3 operator-() const;
    Vec3 operator+(const Vec3 &v) const;
    Vec3 operator-(const Vec3 &v) const;
    float operator*(const Vec3 &v) const;
    Vec3 operator*(float scalar) const;
    Vec3 &operator+=(const Vec3 &v);
    Vec3 &operator-=(const Vec3 &v);
    Vec3 &operator*=(float scalar);

    float length() const;
};

class Vec4Int;
class Vec4 {
public:
    float x = 0, y = 0, z = 0, w = 0;
    Vec4() {}
    Vec4(const Vec4 &v) = default;
    Vec4(Vec4 &&v) = default;
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const Vec4Int &v);

    float &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else if (i == 3) return w; else throw std::runtime_error("Out of bounds"); }
    float operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else if (i == 3) return w; else throw std::runtime_error("Out of bounds"); }

    Vec4 &operator=(const Vec4 &v);
    Vec4 &operator=(const Vec4Int &v);
    bool operator==(const Vec4 &v) const;
    Vec4 operator-() const;
    Vec4 operator+(const Vec4 &v) const;
    Vec4 operator-(const Vec4 &v) const;
    float operator*(const Vec4 &v) const;
    Vec4 operator*(float scalar) const;
    Vec4 &operator+=(const Vec4 &v);
    Vec4 &operator-=(const Vec4 &v);
    Vec4 &operator*=(float scalar);

    float length() const;
};

class Vec2Int {
public:
    int x = 0, y = 0;
    Vec2Int() {}
    Vec2Int(const Vec2Int &v) = default;
    Vec2Int(Vec2Int &&v) = default;
    Vec2Int(int x, int y) : x(x), y(y) {}
    Vec2Int(const Vec2 &v) : x(v.x), y(v.y) {}

    int &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else throw std::runtime_error("Out of bounds"); }
    int operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else throw std::runtime_error("Out of bounds"); }

    Vec2Int &operator=(const Vec2Int &v);
    Vec2Int &operator=(const Vec2 &v);
    bool operator==(const Vec2Int &v) const;
    Vec2Int operator-() const;
    Vec2Int operator+(const Vec2Int &v) const;
    Vec2Int operator-(const Vec2Int &v) const;
    int operator*(const Vec2Int &v) const;
    Vec2Int operator*(int scalar) const;
    Vec2Int &operator+=(const Vec2Int &v);
    Vec2Int &operator-=(const Vec2Int &v);
    Vec2Int &operator*=(int scalar);

    float length() const;
};

class Vec3Int {
public:
    int x = 0, y = 0, z = 0;
    Vec3Int() {}
    Vec3Int(const Vec3Int &v) = default;
    Vec3Int(Vec3Int &&v) = default;
    Vec3Int(int x, int y, int z) : x(x), y(y), z(z) {}
    Vec3Int(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}

    int &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else throw std::runtime_error("Out of bounds"); }
    int operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else throw std::runtime_error("Out of bounds"); }

    Vec3Int &operator=(const Vec3Int &v);
    Vec3Int &operator=(const Vec3 &v);
    bool operator==(const Vec3Int &v) const;
    Vec3Int operator-() const;
    Vec3Int operator+(const Vec3Int &v) const;
    Vec3Int operator-(const Vec3Int &v) const;
    int operator*(const Vec3Int &v) const;
    Vec3Int operator*(int scalar) const;
    Vec3Int &operator+=(const Vec3Int &v);
    Vec3Int &operator-=(const Vec3Int &v);
    Vec3Int &operator*=(int scalar);

    float length() const;
};

class Vec4Int {
public:
    int x = 0, y = 0, z = 0, w = 0;
    Vec4Int() {}
    Vec4Int(const Vec4Int &v) = default;
    Vec4Int(Vec4Int &&v) = default;
    Vec4Int(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
    Vec4Int(const Vec4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    int &operator[](unsigned int i) { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else if (i == 3) return w; else throw std::runtime_error("Out of bounds"); }
    int operator[](unsigned int i) const { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else if (i == 3) return w; else throw std::runtime_error("Out of bounds"); }

    Vec4Int &operator=(const Vec4Int &v);
    Vec4Int &operator=(const Vec4 &v);
    bool operator==(const Vec4Int &v) const;
    Vec4Int operator-() const;
    Vec4Int operator+(const Vec4Int &v) const;
    Vec4Int operator-(const Vec4Int &v) const;
    int operator*(const Vec4Int &v) const;
    Vec4Int operator*(int scalar) const;
    Vec4Int &operator+=(const Vec4Int &v);
    Vec4Int &operator-=(const Vec4Int &v);
    Vec4Int &operator*=(int scalar);

    float length() const;
};

class Mat2x2 {
public:
    float m[4] = {0,0,0,0};

    Mat2x2(){}
    Mat2x2(float m11, float m12, float m21, float m22) :
        m{m11, m12, m21, m22} {}
    Mat2x2(const Mat2x2 &v) = default;
    Mat2x2(Mat2x2 &&v) = default;
    Mat2x2(const Vec2 &v): m{v.x, 0, 0, v.y} {}

    inline float &operator()(unsigned int r, unsigned int c) { return m[r * 2 + c]; }
    inline float operator()(unsigned int r, unsigned int c) const { return m[r * 2 + c]; }

    Mat2x2 &operator=(const Mat2x2 &mat);
    bool operator==(const Mat2x2 &mat) const;
    Mat2x2 operator-() const;
    Mat2x2 operator+(const Mat2x2 &mat) const;
    Mat2x2 operator-(const Mat2x2 &mat) const;
    Mat2x2 operator*(const Mat2x2 &mat) const;
    Vec2 operator*(const Vec2 &v) const;
    Mat2x2 operator*(float scalar) const;
    Mat2x2 &operator+=(const Mat2x2 &mat);
    Mat2x2 &operator-=(const Mat2x2 &mat);
    Mat2x2 &operator*=(const Mat2x2 &mat);
    Mat2x2 &operator*=(float scalar);
};

class Mat3x3 {
public:
    float m[9] = {0,0,0,0,0,0,0,0,0};

    Mat3x3(){}
    Mat3x3(float m11, float m12, float m13,
           float m21, float m22, float m23,
           float m31, float m32, float m33) :
        m{
            m11, m12, m13,
            m21, m22, m23,
            m31, m32, m33
        } {}
    Mat3x3(const Mat3x3 &v) = default;
    Mat3x3(Mat3x3 &&v) = default;
    Mat3x3(const Vec3 &v): m{v.x, 0, 0, 0, v.y, 0, 0, 0, v.z} {}

    inline float &operator()(unsigned int r, unsigned int c) { return m[r * 3 + c]; }
    inline float operator()(unsigned int r, unsigned int c) const { return m[r * 3 + c]; }

    Mat3x3 &operator=(const Mat3x3 &mat);
    bool operator==(const Mat3x3 &mat) const;
    Mat3x3 operator-() const;
    Mat3x3 operator+(const Mat3x3 &mat) const;
    Mat3x3 operator-(const Mat3x3 &mat) const;
    Mat3x3 operator*(const Mat3x3 &mat) const;
    Vec3 operator*(const Vec3 &v) const;
    Mat3x3 operator*(float scalar) const;
    Mat3x3 &operator+=(const Mat3x3 &mat);
    Mat3x3 &operator-=(const Mat3x3 &mat);
    Mat3x3 &operator*=(const Mat3x3 &mat);
    Mat3x3 &operator*=(float scalar);
};

class Mat4x4 {
public:
    float m[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    Mat4x4(){}
    Mat4x4(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44
    ) :
        m{
            m11, m12, m13, m14,
            m21, m22, m23, m24,
            m31, m32, m33, m34,
            m41, m42, m43, m44
        } {}
    Mat4x4(const Mat4x4 &v) = default;
    Mat4x4(Mat4x4 &&v) = default;
    Mat4x4(const Vec4 &v): m{
        v.x, 0, 0, 0,
        0, v.y, 0, 0,
        0, 0, v.z, 0,
        0, 0, 0, v.w
    } {}

    inline float &operator()(unsigned int r, unsigned int c) { return m[r * 4 + c]; }
    inline float operator()(unsigned int r, unsigned int c) const { return m[r * 4 + c]; }

    Mat4x4 &operator=(const Mat4x4 &mat);
    bool operator==(const Mat4x4 &mat) const;
    Mat4x4 operator-() const;
    Mat4x4 operator+(const Mat4x4 &mat) const;
    Mat4x4 operator-(const Mat4x4 &mat) const;
    Mat4x4 operator*(const Mat4x4 &mat) const;
    Vec4 operator*(const Vec4 &v) const;
    Mat4x4 operator*(float scalar) const;
    Mat4x4 &operator+=(const Mat4x4 &mat);
    Mat4x4 &operator-=(const Mat4x4 &mat);
    Mat4x4 &operator*=(const Mat4x4 &mat);
    Mat4x4 &operator*=(float scalar);
};

}

#endif /* PHYBER_ENGINE_PHY_MATH_H */
