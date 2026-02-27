#include "phyber/math.h"
#include <math.h>
#include <string.h>

#include <initializer_list>

using namespace Phyber;

// Vec2

Vec2::Vec2(const Vec2Int &v) : x(v.x), y(v.y) {}

Vec2 &Vec2::operator=(const Vec2 &v) {
    x = v.x;
    y = v.y;
    return *this;
}

Vec2 &Vec2::operator=(const Vec2Int &v) {
    x = v.x;
    y = v.y;
    return *this;
}

bool Vec2::operator==(const Vec2 &v) const {
    return x == v.x && y == v.y;
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2 Vec2::operator+(const Vec2 &v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2 &v) const {
    return Vec2(x - v.x, y - v.y);
}

float Vec2::operator*(const Vec2 &v) const {
    return x * v.x + y * v.y;
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2 &Vec2::operator+=(const Vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2 &Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2 &Vec2::operator*=(const Mat2x2 &m) {
    *this = m * (*this);
    return *this;
}

float Vec2::length() const {
    return sqrt(*this * *this);
}

// Vec3

Vec3::Vec3(const Vec3Int &v) : x(v.x), y(v.y), z(v.z) {}

Vec3 &Vec3::operator=(const Vec3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3 &Vec3::operator=(const Vec3Int &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

bool Vec3::operator==(const Vec3 &v) const {
    return x == v.x && y == v.y && z == v.z;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(const Vec3 &v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3 &v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

float Vec3::operator*(const Vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 &Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3 &Vec3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3 &Vec3::operator*=(const Mat3x3 &m) {
    *this = m * (*this);
    return *this;
}

float Vec3::length() const {
    return sqrt(*this * *this);
}

// Vec4

Vec4::Vec4(const Vec4Int &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

Vec4 &Vec4::operator=(const Vec4 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

Vec4 &Vec4::operator=(const Vec4Int &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

bool Vec4::operator==(const Vec4 &v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

Vec4 Vec4::operator-() const {
    return Vec4(-x, -y, -z, -w);
}

Vec4 Vec4::operator+(const Vec4 &v) const {
    return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vec4 Vec4::operator-(const Vec4 &v) const {
    return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

float Vec4::operator*(const Vec4 &v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vec4 Vec4::operator*(float scalar) const {
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vec4 &Vec4::operator+=(const Vec4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4 &Vec4::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vec4 &Vec4::operator*=(const Mat4x4 &m) {
    *this = m * (*this);
    return *this;
}

float Vec4::length() const {
    return sqrt(*this * *this);
}

// Vec2Int

Vec2Int &Vec2Int::operator=(const Vec2Int &v) {
    x = v.x;
    y = v.y;
    return *this;
}

Vec2Int &Vec2Int::operator=(const Vec2 &v) {
    x = v.x;
    y = v.y;
    return *this;
}

bool Vec2Int::operator==(const Vec2Int &v) const {
    return x == v.x && y == v.y;
}

Vec2Int Vec2Int::operator-() const {
    return Vec2Int(-x, -y);
}

Vec2Int Vec2Int::operator+(const Vec2Int &v) const {
    return Vec2Int(x + v.x, y + v.y);
}

Vec2Int Vec2Int::operator-(const Vec2Int &v) const {
    return Vec2Int(x - v.x, y - v.y);
}

int Vec2Int::operator*(const Vec2Int &v) const {
    return x * v.x + y * v.y;
}

Vec2Int Vec2Int::operator*(int scalar) const {
    return Vec2Int(x * scalar, y * scalar);
}

Vec2Int &Vec2Int::operator+=(const Vec2Int &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vec2Int &Vec2Int::operator-=(const Vec2Int &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2Int &Vec2Int::operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

float Vec2Int::length() const {
    return sqrt(*this * *this);
}

// Vec3Int

Vec3Int &Vec3Int::operator=(const Vec3Int &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3Int &Vec3Int::operator=(const Vec3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

bool Vec3Int::operator==(const Vec3Int &v) const {
    return x == v.x && y == v.y && z == v.z;
}

Vec3Int Vec3Int::operator-() const {
    return Vec3Int(-x, -y, -z);
}

Vec3Int Vec3Int::operator+(const Vec3Int &v) const {
    return Vec3Int(x + v.x, y + v.y, z + v.z);
}

Vec3Int Vec3Int::operator-(const Vec3Int &v) const {
    return Vec3Int(x - v.x, y - v.y, z - v.z);
}

int Vec3Int::operator*(const Vec3Int &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vec3Int Vec3Int::operator*(int scalar) const {
    return Vec3Int(x * scalar, y * scalar, z * scalar);
}

Vec3Int &Vec3Int::operator+=(const Vec3Int &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3Int &Vec3Int::operator-=(const Vec3Int &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3Int &Vec3Int::operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

float Vec3Int::length() const {
    return sqrt(*this * *this);
}

// Vec4Int

Vec4Int &Vec4Int::operator=(const Vec4Int &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

Vec4Int &Vec4Int::operator=(const Vec4 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

bool Vec4Int::operator==(const Vec4Int &v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

Vec4Int Vec4Int::operator-() const {
    return Vec4Int(-x, -y, -z, -w);
}

Vec4Int Vec4Int::operator+(const Vec4Int &v) const {
    return Vec4Int(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vec4Int Vec4Int::operator-(const Vec4Int &v) const {
    return Vec4Int(x - v.x, y - v.y, z - v.z, w - v.w);
}

int Vec4Int::operator*(const Vec4Int &v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vec4Int Vec4Int::operator*(int scalar) const {
    return Vec4Int(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vec4Int &Vec4Int::operator+=(const Vec4Int &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4Int &Vec4Int::operator-=(const Vec4Int &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4Int &Vec4Int::operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

float Vec4Int::length() const {
    return sqrt(*this * *this);
}

// Mat2x2

Mat2x2 &Mat2x2::operator=(const Mat2x2 &mat) {
    memcpy(m, mat.m, sizeof(float) * 4);
    return *this;
}

bool Mat2x2::operator==(const Mat2x2 &mat) const {
    return memcmp(m, mat.m, sizeof(float) * 4) == 0;
}

Mat2x2 Mat2x2::operator-() const {
    return Mat2x2(-m[0], -m[1], -m[2], -m[3]);
}

Mat2x2 Mat2x2::operator+(const Mat2x2 &mat) const {
    return Mat2x2(
        m[0] + mat.m[0], m[1] + mat.m[1],
        m[2] + mat.m[2], m[3] + mat.m[3]
    );
}

Mat2x2 Mat2x2::operator-(const Mat2x2 &mat) const {
    return Mat2x2(
        m[0] - mat.m[0], m[1] - mat.m[1],
        m[2] - mat.m[2], m[3] - mat.m[3]
    );
}

Mat2x2 Mat2x2::operator*(const Mat2x2 &mat) const {
    const float m11 = (*this)(0,0)*mat(0,0) +
                      (*this)(0,1)*mat(1,0);
    const float m12 = (*this)(0,0)*mat(0,1) +
                      (*this)(0,1)*mat(1,1);
    const float m21 = (*this)(1,0)*mat(0,0) +
                      (*this)(1,1)*mat(1,0);
    const float m22 = (*this)(1,0)*mat(0,1) +
                      (*this)(1,1)*mat(1,1);
    return Mat2x2(m11, m12, m21, m22);
}

Vec2 Mat2x2::operator*(const Vec2 &v) const {
    return Vec2(
        (*this)(0,0)*v.x + (*this)(0,1)*v.y,
        (*this)(1,0)*v.x + (*this)(1,1)*v.y
    );
}

Mat2x2 Mat2x2::operator*(float scalar) const {
    return Mat2x2(
        m[0]*scalar, m[1]*scalar,
        m[2]*scalar, m[3]*scalar
    );
}

Mat2x2 &Mat2x2::operator+=(const Mat2x2 &mat) {
    m[0] += mat.m[0];
    m[1] += mat.m[1];
    m[2] += mat.m[2];
    m[3] += mat.m[3];
    return *this;
}

Mat2x2 &Mat2x2::operator-=(const Mat2x2 &mat) {
    m[0] -= mat.m[0];
    m[1] -= mat.m[1];
    m[2] -= mat.m[2];
    m[3] -= mat.m[3];
    return *this;
}

Mat2x2 &Mat2x2::operator*=(const Mat2x2 &mat) {
    (*this) = (*this) * mat;
    return *this;
}

Mat2x2 &Mat2x2::operator*=(float scalar) {
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    return *this;
}

Mat2x2 Mat2x2::rotation_matrix(float radians) {
    const float c = cos(radians);
    const float s = sin(radians);
    return Mat2x2(
        c, -s, s, c
    );
}

// Mat3x3

Mat3x3 &Mat3x3::operator=(const Mat3x3 &mat) {
    memcpy(m, mat.m, sizeof(float) * 9);
    return *this;
}

bool Mat3x3::operator==(const Mat3x3 &mat) const {
    return memcmp(m, mat.m, sizeof(float) * 9) == 0;
}

Mat3x3 Mat3x3::operator-() const {
    return Mat3x3(
        -m[0], -m[1], -m[2],
        -m[3], -m[4], -m[5],
        -m[6], -m[7], -m[8]
    );
}

Mat3x3 Mat3x3::operator+(const Mat3x3 &mat) const {
    return Mat3x3(
        m[0] + mat.m[0], m[1] + mat.m[1], m[2] + mat.m[2],
        m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
        m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8]
    );
}

Mat3x3 Mat3x3::operator-(const Mat3x3 &mat) const {
    return Mat3x3(
        m[0] - mat.m[0], m[1] - mat.m[1], m[2] - mat.m[2],
        m[3] - mat.m[3], m[4] - mat.m[4], m[5] - mat.m[5],
        m[6] - mat.m[6], m[7] - mat.m[7], m[8] - mat.m[8]
    );
}

Mat3x3 Mat3x3::operator*(const Mat3x3 &mat) const {
    Mat3x3 out;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            out(r,c) =
                (*this)(r,0) * mat(0,c) +
                (*this)(r,1) * mat(1,c) +
                (*this)(r,2) * mat(2,c);
        }
    }
    return out;
}

Vec3 Mat3x3::operator*(const Vec3 &v) const {
    return Vec3(
        (*this)(0,0)*v.x + (*this)(0,1)*v.y + (*this)(0,2)*v.z,
        (*this)(1,0)*v.x + (*this)(1,1)*v.y + (*this)(1,2)*v.z,
        (*this)(2,0)*v.x + (*this)(2,1)*v.y + (*this)(2,2)*v.z
    );
}

Mat3x3 Mat3x3::operator*(float scalar) const {
    return Mat3x3(
        m[0]*scalar, m[1]*scalar, m[2]*scalar,
        m[3]*scalar, m[4]*scalar, m[5]*scalar,
        m[6]*scalar, m[7]*scalar, m[8]*scalar
    );
}

Mat3x3 &Mat3x3::operator+=(const Mat3x3 &mat) {
    for (int i = 0; i < 9; ++i) {
        m[i] += mat.m[i];
    }
    return *this;
}

Mat3x3 &Mat3x3::operator-=(const Mat3x3 &mat) {
    for (int i = 0; i < 9; ++i) {
        m[i] -= mat.m[i];
    }
    return *this;
}

Mat3x3 &Mat3x3::operator*=(const Mat3x3 &mat) {
    (*this) = (*this) * mat;
    return *this;
}

Mat3x3 &Mat3x3::operator*=(float scalar) {
    for (int i = 0; i < 9; ++i) {
        m[i] *= scalar;
    }
    return *this;
}

Mat3x3 Mat3x3::rotation_matrix_x(float radians) {
    const float c = cos(radians);
    const float s = sin(radians);
    return Mat3x3(
        1, 0, 0,
        0, c, -s,
        0, s, c
    );
}

Mat3x3 Mat3x3::rotation_matrix_y(float radians) {
    const float c = cos(radians);
    const float s = sin(radians);
    return Mat3x3(
        c, 0, s,
        0, 1, 0,
        -s, 0, c
    );
}

Mat3x3 Mat3x3::rotation_matrix_z(float radians) {
    const float c = cos(radians);
    const float s = sin(radians);
    return Mat3x3(
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    );
}


Mat3x3 Mat3x3::rotation_matrix(const Vec3 *radians) {
    return
        Mat3x3::rotation_matrix_x(radians->x) *
        Mat3x3::rotation_matrix_y(radians->y) *
        Mat3x3::rotation_matrix_z(radians->z);
}

Mat3x3 Mat3x3::rotation_matrix(const Vec3Int *radians) {
    return
        Mat3x3::rotation_matrix_x(static_cast<float>(radians->x)) *
        Mat3x3::rotation_matrix_y(static_cast<float>(radians->y)) *
        Mat3x3::rotation_matrix_z(static_cast<float>(radians->z));
}

Mat3x3 Mat3x3::translation_2d_matrix(const Vec2 *translation) {
    return Mat3x3({
        1, 0, translation->x,
        0, 1, translation->y,
        0, 0, 1
    });
}

Mat3x3 Mat3x3::translation_2d_matrix(const Vec2Int *translation) {
    return Mat3x3({
        1, 0, static_cast<float>(translation->x),
        0, 1, static_cast<float>(translation->y),
        0, 0, 1
    });
}

// Mat4x4

Mat4x4 &Mat4x4::operator=(const Mat4x4 &mat) {
    memcpy(m, mat.m, sizeof(float) * 16);
    return *this;
}

bool Mat4x4::operator==(const Mat4x4 &mat) const {
    return memcmp(m, mat.m, sizeof(float) * 16) == 0;
}

Mat4x4 Mat4x4::operator-() const {
    return Mat4x4(
        -m[0], -m[1], -m[2], -m[3],
        -m[4], -m[5], -m[6], -m[7],
        -m[8], -m[9], -m[10], -m[11],
        -m[12], -m[13], -m[14], -m[15]
    );
}

Mat4x4 Mat4x4::operator+(const Mat4x4 &mat) const {
    return Mat4x4(
        m[0] + mat.m[0],
        m[1] + mat.m[1],
        m[2] + mat.m[2],
        m[3] + mat.m[3],
        m[4] + mat.m[4],
        m[5] + mat.m[5],
        m[6] + mat.m[6],
        m[7] + mat.m[7],
        m[8] + mat.m[8],
        m[9] + mat.m[9],
        m[10] + mat.m[10],
        m[11] + mat.m[11],
        m[12] + mat.m[12],
        m[13] + mat.m[13],
        m[14] + mat.m[14],
        m[15] + mat.m[15]
    );
}

Mat4x4 Mat4x4::operator-(const Mat4x4 &mat) const {
    return Mat4x4(
        m[0] - mat.m[0],
        m[1] - mat.m[1],
        m[2] - mat.m[2],
        m[3] - mat.m[3],
        m[4] - mat.m[4],
        m[5] - mat.m[5],
        m[6] - mat.m[6],
        m[7] - mat.m[7],
        m[8] - mat.m[8],
        m[9] - mat.m[9],
        m[10] - mat.m[10],
        m[11] - mat.m[11],
        m[12] - mat.m[12],
        m[13] - mat.m[13],
        m[14] - mat.m[14],
        m[15] - mat.m[15]
    );
}

Mat4x4 Mat4x4::operator*(const Mat4x4 &mat) const {
    Mat4x4 out;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            out(r,c) =
                (*this)(r,0) * mat(0,c) +
                (*this)(r,1) * mat(1,c) +
                (*this)(r,2) * mat(2,c) +
                (*this)(r,3) * mat(3,c);
        }
    }
    return out;
}

Vec4 Mat4x4::operator*(const Vec4 &v) const {
    return Vec4(
        (*this)(0,0)*v.x + (*this)(0,1)*v.y + (*this)(0,2)*v.z + (*this)(0,3)*v.w,
        (*this)(1,0)*v.x + (*this)(1,1)*v.y + (*this)(1,2)*v.z + (*this)(1,3)*v.w,
        (*this)(2,0)*v.x + (*this)(2,1)*v.y + (*this)(2,2)*v.z + (*this)(2,3)*v.w,
        (*this)(3,0)*v.x + (*this)(3,1)*v.y + (*this)(3,2)*v.z + (*this)(3,3)*v.w
    );
}

Mat4x4 Mat4x4::operator*(float scalar) const {
    return Mat4x4(
        m[0]*scalar, m[1]*scalar, m[2]*scalar, m[3]*scalar,
        m[4]*scalar, m[5]*scalar, m[6]*scalar, m[7]*scalar,
        m[8]*scalar, m[9]*scalar, m[10]*scalar, m[11]*scalar,
        m[12]*scalar, m[13]*scalar, m[14]*scalar, m[15]*scalar
    );
}

Mat4x4 &Mat4x4::operator+=(const Mat4x4 &mat) {
    for (int i = 0; i < 16; ++i) {
        m[i] += mat.m[i];
    }
    return *this;
}

Mat4x4 &Mat4x4::operator-=(const Mat4x4 &mat) {
    for (int i = 0; i < 16; ++i) {
        m[i] -= mat.m[i];
    }
    return *this;
}

Mat4x4 &Mat4x4::operator*=(const Mat4x4 &mat) {
    (*this) = (*this) * mat;
    return *this;
}

Mat4x4 &Mat4x4::operator*=(float scalar) {
    for (int i = 0; i < 16; ++i) {
        m[i] *= scalar;
    }
    return *this;
}

float radians_to_range(float rad) {
    constexpr float pi2 = M_PI * 2;
    constexpr float pi2_inv = 1 / pi2;
    return rad - pi2 * floorf(rad * pi2_inv);
}
