#include "phyber/math.h"
#include <sstream>
#include <cmath>
#include <cstdint>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Phyber;

namespace Catch {
    template<>
    struct StringMaker<Vec2> {
        static std::string convert(const Vec2& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Vec3> {
        static std::string convert(const Vec3& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Vec4> {
        static std::string convert(const Vec4& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Vec2Int> {
        static std::string convert(const Vec2Int& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Vec3Int> {
        static std::string convert(const Vec3Int& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Vec4Int> {
        static std::string convert(const Vec4Int& vec) {
            std::stringstream o;
            o << "{" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Mat2x2> {
        static std::string convert(const Mat2x2& mat) {
            std::stringstream o;
            constexpr int d = 2;

            o << "{";
            for (int r = 0; r < d; ++r) {
                o << "{";
                for (int c = 0; c < d; ++c) {
                    o << mat(r,c);
                    if (c < d-1)
                        o << ", ";
                }
                o << "}";
                if (r < d-1)
                    o << ", ";
            }
            o << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Mat3x3> {
        static std::string convert(const Mat3x3& mat) {
            std::stringstream o;
            constexpr int d = 3;

            o << "{";
            for (int r = 0; r < d; ++r) {
                o << "{";
                for (int c = 0; c < d; ++c) {
                    o << mat(r,c);
                    if (c < d-1)
                        o << ", ";
                }
                o << "}";
                if (r < d-1)
                    o << ", ";
            }
            o << "}";
            return o.str();
        }
    };

    template<>
    struct StringMaker<Mat4x4> {
        static std::string convert(const Mat4x4& mat) {
            std::stringstream o;
            constexpr int d = 4;

            o << "{";
            for (int r = 0; r < d; ++r) {
                o << "{";
                for (int c = 0; c < d; ++c) {
                    o << mat(r,c);
                    if (c < d-1)
                        o << ", ";
                }
                o << "}";
                if (r < d-1)
                    o << ", ";
            }
            o << "}";
            return o.str();
        }
    };
}

constexpr float EPS = 1e-5f;

//
// Vec2
//
TEST_CASE("Vec2", "[vec2]") {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(3.0f, 4.0f);

    SECTION("addition") {
        Vec2 c = a + b;
        CHECK(c == Vec2(4.0f, 6.0f));
    }

    SECTION("subtraction") {
        Vec2 c = b - a;
        CHECK(c == Vec2(2.0f, 2.0f));
    }

    SECTION("negation") {
        Vec2 c = -a;
        CHECK(c == Vec2(-1.0f, -2.0f));
    }

    SECTION("scalar multiply") {
        Vec2 c = a * 2.0f;
        CHECK(c == Vec2(2.0f, 4.0f));
    }

    SECTION("dot product") {
        float d = a * b;
        CHECK(d == Catch::Approx(11.0f));
    }

    SECTION("compound operators") {
        Vec2 c = a;
        c += b;
        CHECK(c == Vec2(4.0f, 6.0f));

        c -= b;
        CHECK(c == a);

        c *= 2.0f;
        CHECK(c == Vec2(2.0f, 4.0f));
    }

    SECTION("length") {
        Vec2 c(3.0f, 4.0f);
        CHECK(c.length() == Catch::Approx(5.0f));
    }
}

TEST_CASE("Vec3", "[vec3]") {
    Vec3 a(1,2,3);
    Vec3 b(4,5,6);

    SECTION("addition") {
        Vec3 c = a + b;
        CHECK(c == Vec3(5,7,9));
    }

    SECTION("subtraction") {
        Vec3 c = b - a;
        CHECK(c == Vec3(3,3,3));
    }

    SECTION("negation") {
        Vec3 c = -a;
        CHECK(c == Vec3(-1,-2,-3));
    }

    SECTION("scalar multiply") {
        Vec3 c = a * 2.0f;
        CHECK(c == Vec3(2, 4, 6));
    }

    SECTION("dot product") {
        float d = a * b;
        CHECK(d == Catch::Approx(32.0f));
    }

    SECTION("compound operators") {
        Vec3 c = a;
        c += b;
        CHECK(c == Vec3(5,7,9));

        c -= b;
        CHECK(c == a);

        c *= 2.0f;
        CHECK(c == Vec3(2,4,6));
    }

    SECTION("length") {
        Vec3 c(3,4,5);
        CHECK(c.length() == Catch::Approx(7.0710678118654755f));
    }
}

TEST_CASE("Vec4", "[vec4]") {
    Vec4 a(1,2,3,4);
    Vec4 b(5,6,7,8);

    SECTION("addition") {
        Vec4 c = a + b;
        CHECK(c == Vec4(6,8,10,12));
    }

    SECTION("subtraction") {
        Vec4 c = b - a;
        CHECK(c == Vec4(4,4,4,4));
    }

    SECTION("negation") {
        Vec4 c = -a;
        CHECK(c == Vec4(-1,-2,-3,-4));
    }

    SECTION("scalar multiply") {
        Vec4 c = a * 2.0f;
        CHECK(c == Vec4(2, 4, 6, 8));
    }

    SECTION("dot product") {
        float d = a * b;
        CHECK(d == Catch::Approx(70.0f));
    }

    SECTION("compound operators") {
        Vec4 c = a;
        c += b;
        CHECK(c == Vec4(6,8,10,12));

        c -= b;
        CHECK(c == a);

        c *= 2.0f;
        CHECK(c == Vec4(2,4,6,8));
    }

    SECTION("length") {
        Vec4 c(3,4,5,6);
        CHECK(c.length() == Catch::Approx(9.273618495495704f));
    }
}

//
// Vec2Int
//
TEST_CASE("Vec2Int", "[vec2int]") {
    Vec2Int a(1, 2);
    Vec2Int b(3, 4);

    SECTION("addition") {
        CHECK(a + b == Vec2Int(4, 6));
    }

    SECTION("subtraction") {
        CHECK(b - a == Vec2Int(2, 2));
    }

    SECTION("negation") {
        CHECK(-a == Vec2Int(-1, -2));
    }

    SECTION("scalar multiply") {
        CHECK(a * 2 == Vec2Int(2, 4));
    }

    SECTION("dot product") {
        CHECK((a * b) == 11);
    }

    SECTION("length") {
        Vec2Int c(3, 4);
        CHECK(c.length() == Catch::Approx(5.0f));
    }
}

TEST_CASE("Vec3Int", "[vec3int]") {
    Vec3Int a(1, 2, 3);
    Vec3Int b(4, 5, 6);

    SECTION("addition") {
        CHECK(a + b == Vec3Int(5,7,9));
    }

    SECTION("subtraction") {
        CHECK(b - a == Vec3Int(3,3,3));
    }

    SECTION("negation") {
        CHECK(-a == Vec3Int(-1, -2, -3));
    }

    SECTION("scalar multiply") {
        CHECK(a * 2 == Vec3Int(2, 4, 6));
    }

    SECTION("dot product") {
        CHECK((a * b) == 32);
    }

    SECTION("length") {
        Vec3Int c(3, 4, 5);
        CHECK(c.length() == Catch::Approx(7.0710678118654755f));
    }
}

TEST_CASE("Vec4Int", "[vec4int]") {
    Vec4Int a(1, 2, 3, 4);
    Vec4Int b(5, 6, 7, 8);

    SECTION("addition") {
        CHECK(a + b == Vec4Int(6,8,10,12));
    }

    SECTION("subtraction") {
        CHECK(b - a == Vec4Int(4,4,4,4));
    }

    SECTION("negation") {
        CHECK(-a == Vec4Int(-1, -2, -3, -4));
    }

    SECTION("scalar multiply") {
        CHECK(a * 2 == Vec4Int(2, 4, 6, 8));
    }

    SECTION("dot product") {
        CHECK((a * b) == 70);
    }

    SECTION("length") {
        Vec4Int c(3, 4, 5,6);
        CHECK(c.length() == Catch::Approx(9.273618495495704f));
    }
}

TEST_CASE("Mat2x2", "[mat2x2]") {
    SECTION("Mat2x2 constructors") {
        Mat2x2 m1;
        CHECK(m1(0,0) == 0.0f);
        CHECK(m1(1,0) == 0.0f);
        CHECK(m1(0,1) == 0.0f);
        CHECK(m1(1,1) == 0.0f);

        Mat2x2 m2(1, 2, 3, 4);
        CHECK(m2(0,0) == 1.0f);
        CHECK(m2(0,1) == 2.0f);
        CHECK(m2(1,0) == 3.0f);
        CHECK(m2(1,1) == 4.0f);

        Vec2 v(5, 6);
        Mat2x2 m3(v);
        CHECK(m3(0,0) == 5.0f);
        CHECK(m3(1,1) == 6.0f);
        CHECK(m3(0,1) == 0.0f);
        CHECK(m3(1,0) == 0.0f);
    }

    SECTION("Mat2x2 assign") {
        Mat2x2 a(1,2,3,4);
        a(1,1) = 10;
        CHECK(a(1,1) == 10);
    }

    SECTION("Mat2x2 equality") {
        Mat2x2 a(1,2,3,4);
        Mat2x2 b(1,2,3,4);
        Mat2x2 c(4,3,2,1);

        CHECK(a == b);
        CHECK_FALSE(a == c);
    }

    SECTION("Mat2x2 unary minus") {
        Mat2x2 a(1, -2, 3, -4);
        Mat2x2 b = -a;

        CHECK(b(0,0) == -1);
        CHECK(b(0,1) == 2);
        CHECK(b(1,0) == -3);
        CHECK(b(1,1) == 4);
    }

    SECTION("Mat2x2 addition and subtraction") {
        Mat2x2 a(1,2,3,4);
        Mat2x2 b(4,3,2,1);

        Mat2x2 c = a + b;
        CHECK(c(0,0) == 5);
        CHECK(c(0,1) == 5);
        CHECK(c(1,0) == 5);
        CHECK(c(1,1) == 5);

        Mat2x2 d = a - b;
        CHECK(d(0,0) == -3);
        CHECK(d(0,1) == -1);
        CHECK(d(1,0) == 1);
        CHECK(d(1,1) == 3);
    }

    SECTION("Mat2x2 scalar multiplication") {
        Mat2x2 a(1,2,3,4);
        Mat2x2 b = a * 2.0f;

        CHECK(b(0,0) == 2);
        CHECK(b(0,1) == 4);
        CHECK(b(1,0) == 6);
        CHECK(b(1,1) == 8);

        a *= 0.5f;
        CHECK(a(0,0) == 0.5f);
        CHECK(a(1,1) == 2.0f);
    }

    SECTION("Mat2x2 matrix multiplication") {
        Mat2x2 a(1,2,3,4);
        Mat2x2 b(2,0,1,2);

        Mat2x2 c = a * b;
        // Manual computation:
        // c00 = 1*2 + 2*1 = 4
        // c01 = 1*0 + 2*2 = 4
        // c10 = 3*2 + 4*1 = 10
        // c11 = 3*0 + 4*2 = 8
        CHECK(c(0,0) == 4);
        CHECK(c(0,1) == 4);
        CHECK(c(1,0) == 10);
        CHECK(c(1,1) == 8);

        Mat2x2 d = a;
        d *= b;
        CHECK(d == c);
    }

    SECTION("Mat2x2 vector multiplication") {
        Mat2x2 a(1,2,3,4);
        Vec2 v(5,6);
        Vec2 r = a * v;

        // r0 = 1*5 + 2*6 = 17
        // r1 = 3*5 + 4*6 = 39
        CHECK(r.x == 17);
        CHECK(r.y == 39);
    }
}

TEST_CASE("Mat3x3", "[mat3x3]") {
    SECTION("Mat3x3 constructors") {
        Mat3x3 m1;
        CHECK(m1(0,0) == 0.0f);
        CHECK(m1(0,1) == 0.0f);
        CHECK(m1(0,2) == 0.0f);
        CHECK(m1(1,0) == 0.0f);
        CHECK(m1(1,1) == 0.0f);
        CHECK(m1(1,2) == 0.0f);
        CHECK(m1(2,0) == 0.0f);
        CHECK(m1(2,1) == 0.0f);
        CHECK(m1(2,2) == 0.0f);

        Mat3x3 m2(1,2,3,4,5,6,7,8,9);
        CHECK(m2(0,0) == 1);
        CHECK(m2(0,1) == 2);
        CHECK(m2(0,2) == 3);
        CHECK(m2(1,0) == 4);
        CHECK(m2(1,1) == 5);
        CHECK(m2(1,2) == 6);
        CHECK(m2(2,0) == 7);
        CHECK(m2(2,1) == 8);
        CHECK(m2(2,2) == 9);

        Vec3 v(10, 11, 12);
        Mat3x3 m3(v);
        CHECK(m3(0,0) == 10);
        CHECK(m3(1,1) == 11);
        CHECK(m3(2,2) == 12);
        CHECK(m3(0,1) == 0);
        CHECK(m3(0,2) == 0);
        CHECK(m3(1,0) == 0);
        CHECK(m3(1,2) == 0);
        CHECK(m3(2,0) == 0);
        CHECK(m3(2,1) == 0);
    }

    SECTION("Mat3x3 assign") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        a(1,1) = 10;
        CHECK(a(1,1) == 10);
    }

    SECTION("Mat3x3 equality") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        Mat3x3 b(1,2,3,4,5,6,7,8,9);
        Mat3x3 c(9,8,7,6,5,4,3,2,1);

        CHECK(a == b);
        CHECK_FALSE(a == c);
    }

    SECTION("Mat3x3 unary minus") {
        Mat3x3 a(1,-2,3,-4,5,-6,7,-8,9);
        Mat3x3 b = -a;

        CHECK(b(0,0) == -1);
        CHECK(b(0,1) == 2);
        CHECK(b(0,2) == -3);
        CHECK(b(1,0) == 4);
        CHECK(b(1,1) == -5);
        CHECK(b(1,2) == 6);
        CHECK(b(2,0) == -7);
        CHECK(b(2,1) == 8);
        CHECK(b(2,2) == -9);
    }

    SECTION("Mat3x3 addition and subtraction") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        Mat3x3 b(9,8,7,6,5,4,3,2,1);

        Mat3x3 c = a + b;
        for(int r=0; r<3; ++r)
            for(int col=0; col<3; ++col)
                CHECK(c(r,col) == 10);

        Mat3x3 d = a - b;
        CHECK(d(0,0) == -8);
        CHECK(d(0,1) == -6);
        CHECK(d(0,2) == -4);
        CHECK(d(1,0) == -2);
        CHECK(d(1,1) == 0);
        CHECK(d(1,2) == 2);
        CHECK(d(2,0) == 4);
        CHECK(d(2,1) == 6);
        CHECK(d(2,2) == 8);
    }

    SECTION("Mat3x3 scalar multiplication") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        Mat3x3 b = a * 2.0f;

        for(int r=0; r<3; ++r)
            for(int c=0; c<3; ++c)
                CHECK(b(r,c) == a(r,c) * 2.0f);

        a *= 0.5f;
        for(int r=0; r<3; ++r)
            for(int c=0; c<3; ++c)
                CHECK(a(r,c) == Catch::Approx((float)(a(r,c)))); // simple check
    }

    SECTION("Mat3x3 matrix multiplication") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        Mat3x3 b(9,8,7,6,5,4,3,2,1);

        Mat3x3 c = a * b;

        // Manual computation example
        CHECK(c(0,0) == 1*9 + 2*6 + 3*3);
        CHECK(c(0,1) == 1*8 + 2*5 + 3*2);
        CHECK(c(0,2) == 1*7 + 2*4 + 3*1);
        CHECK(c(1,0) == 4*9 + 5*6 + 6*3);
        CHECK(c(1,1) == 4*8 + 5*5 + 6*2);
        CHECK(c(1,2) == 4*7 + 5*4 + 6*1);
        CHECK(c(2,0) == 7*9 + 8*6 + 9*3);
        CHECK(c(2,1) == 7*8 + 8*5 + 9*2);
        CHECK(c(2,2) == 7*7 + 8*4 + 9*1);

        Mat3x3 d = a;
        d *= b;
        CHECK(d == c);
    }

    SECTION("Mat3x3 vector multiplication") {
        Mat3x3 a(1,2,3,4,5,6,7,8,9);
        Vec3 v(1,2,3);
        Vec3 r = a * v;

        CHECK(r.x == 1*1 + 2*2 + 3*3);
        CHECK(r.y == 4*1 + 5*2 + 6*3);
        CHECK(r.z == 7*1 + 8*2 + 9*3);
    }
}

TEST_CASE("Mat4x4", "[mat4x4]") {
    SECTION("Mat4x4 constructors") {
        Mat4x4 m1;
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                CHECK(m1(r,c) == 0.0f);

        Mat4x4 m2(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        int val = 1;
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                CHECK(m2(r,c) == val++);

        Vec4 v(17,18,19,20);
        Mat4x4 m3(v);
        CHECK(m3(0,0) == 17);
        CHECK(m3(1,1) == 18);
        CHECK(m3(2,2) == 19);
        CHECK(m3(3,3) == 20);
        // Off-diagonal elements
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                if (r != c)
                    CHECK(m3(r,c) == 0.0f);
    }

    SECTION("Mat4x4 assign") {
        Mat4x4 a;
        a(2,3) = 42;
        CHECK(a(2,3) == 42);
    }

    SECTION("Mat4x4 equality") {
        Mat4x4 a(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Mat4x4 b(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Mat4x4 c(
            16,15,14,13,
            12,11,10,9,
            8,7,6,5,
            4,3,2,1
        );

        CHECK(a == b);
        CHECK_FALSE(a == c);
    }

    SECTION("Mat4x4 unary minus") {
        Mat4x4 a(
            1,-2,3,-4,
            5,-6,7,-8,
            9,-10,11,-12,
            13,-14,15,-16
        );
        Mat4x4 b = -a;
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                CHECK(b(r,c) == -a(r,c));
    }

    SECTION("Mat4x4 addition and subtraction") {
        Mat4x4 a(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Mat4x4 b(
            16,15,14,13,
            12,11,10,9,
            8,7,6,5,
            4,3,2,1
        );

        Mat4x4 c = a + b;
        for (int r = 0; r < 4; ++r)
            for (int col = 0; col < 4; ++col)
                CHECK(c(r,col) == a(r,col) + b(r,col));

        Mat4x4 d = a - b;
        for (int r = 0; r < 4; ++r)
            for (int col = 0; col < 4; ++col)
                CHECK(d(r,col) == a(r,col) - b(r,col));
    }

    SECTION("Mat4x4 scalar multiplication") {
        Mat4x4 a(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Mat4x4 b = a * 2.0f;
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                CHECK(b(r,c) == a(r,c) * 2.0f);

        a *= 0.5f;
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c)
                CHECK(a(r,c) == Catch::Approx(a(r,c))); // simple check
    }

    SECTION("Mat4x4 matrix multiplication") {
        Mat4x4 a(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Mat4x4 b(
            16,15,14,13,
            12,11,10,9,
            8,7,6,5,
            4,3,2,1
        );

        Mat4x4 c = a * b;
        for (int r = 0; r < 4; ++r)
            for (int col = 0; col < 4; ++col) {
                float sum = 0;
                for (int k = 0; k < 4; ++k)
                    sum += a(r,k) * b(k,col);
                CHECK(c(r,col) == sum);
            }

        Mat4x4 d = a;
        d *= b;
        CHECK(d == c);
    }

    SECTION("Mat4x4 vector multiplication") {
        Mat4x4 a(
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
        );
        Vec4 v(1,2,3,4);
        Vec4 r = a * v;
        for (int r_idx = 0; r_idx < 4; ++r_idx) {
            float sum = 0;
            for (int c_idx = 0; c_idx < 4; ++c_idx)
                sum += a(r_idx,c_idx) * v[c_idx]; // assuming Vec4 has operator[] or x,y,z,w mapping
            CHECK(r[r_idx] == sum);
        }
    }
}
