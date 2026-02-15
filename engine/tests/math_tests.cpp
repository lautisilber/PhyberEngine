#include "phyber/math.h"
#include <cmath>
#include <cstdint>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Phyber;

namespace Catch {
    template <typename T, size_t N, std::unsigned_integral I, bool RANGE_CHECK>
    struct StringMaker<PhyberVecN_T<T, N, I, RANGE_CHECK>> {
        static std::string convert(const PhyberVecN_T<T, N, I, RANGE_CHECK>& vec) {
            std::string result = "{";
            for (I i = 0; i < N; ++i) {
                result += std::to_string(vec[i]);
                if (i < N - 1) result += ", ";
            }
            result += "}";
            return result;
        }
    };

    template <typename T, size_t N, std::unsigned_integral I, bool RANGE_CHECK>
    struct StringMaker<PhyberMatNxN_T<T, N, I, RANGE_CHECK>> {
        static std::string convert(const PhyberMatNxN_T<T, N, I, RANGE_CHECK>& mat) {
            std::string result = "{";
            for (I r = 0; r < N; ++r) {
                result += "{";
                for (I c = 0; c < N; ++c) {
                    result += std::to_string(mat(r, c));
                    if (c < N - 1) result += ", ";
                }
                result += "}";
                if (r < N - 1) result += ", ";
            }
            result += "}";
            return result;
        }
    };
}

TEST_CASE("vectors 2d", "[vectors2]") {
    SECTION("Basic initialization") {
        {
            PhyberVec2_int u;
            CHECK(u[0] == 0);
            CHECK(u[1] == 0);
        }

        {
            PhyberVec2_int v({1, 2});
            CHECK(v[0] == 1);
            CHECK(v[1] == 2);

            CHECK(v.x() == 1);
            CHECK(v.y() == 2);

            v[0] = 3;
            v[1] = 4;
            CHECK(v[0] == 3);
            CHECK(v[1] == 4);

            v.x() = 5;
            v.y() = 6;
            CHECK(v.x() == 5);
            CHECK(v.y() == 6);
        }
    }

    SECTION("Unary operations") {
        PhyberVec2_int v({1, 2});

        CHECK_THROWS(v[2]);
        CHECK_THAT(v.length(), Catch::Matchers::WithinRel(sqrt(1 + 2*2), 1e-6));
        CHECK(-v[0] == -1.0);
        CHECK(-v[1] == -2.0);
    }

    SECTION("Binary operators") {
        PhyberVec2_int v({1, 2});
        PhyberVec2_int u({3, 4});
        PhyberVec2_int w({-1, -2});

        CHECK(v == v);
        CHECK(v != u);
        CHECK(-v == w);
        CHECK(v == std::vector<int>({1, 2}));
        CHECK(v != std::vector<int>({1, 3}));
        CHECK(v != std::vector<int>({1, 2, 3}));

        CHECK((v * 2) == std::vector<int>({2, 4}));
        CHECK((v + 3) == std::vector<int>({4, 5}));
        CHECK((v - 3) == std::vector<int>({-2, -1}));

        CHECK((v * u) == 11);
        CHECK((v + u) == std::vector<int>({4, 6}));
        CHECK((v - u) == std::vector<int>({-2, -2}));
    }
}

TEST_CASE("vectors 3d", "[vectors3]") {
    SECTION("Basic initialization") {
        {
            PhyberVec3_int u;
            CHECK(u[0] == 0);
            CHECK(u[1] == 0);
            CHECK(u[2] == 0);
        }

        {
            PhyberVec3_int v({1, 2, 3});
            CHECK(v[0] == 1);
            CHECK(v[1] == 2);
            CHECK(v[2] == 3);

            CHECK(v.x() == 1);
            CHECK(v.y() == 2);
            CHECK(v.z() == 3);

            v[0] = 4;
            v[1] = 5;
            v[2] = 6;
            CHECK(v[0] == 4);
            CHECK(v[1] == 5);
            CHECK(v[2] == 6);

            v.x() = 7;
            v.y() = 8;
            v.z() = 9;
            CHECK(v.x() == 7);
            CHECK(v.y() == 8);
            CHECK(v.z() == 9);
        }
    }

    SECTION("Unary operations") {
        PhyberVec3_int v({1, 2, 3});

        CHECK_THROWS(v[3]);
        CHECK_THAT(v.length(), Catch::Matchers::WithinRel(sqrt(1*1 + 2*2 + 3*3), 1e-6));
        CHECK(-v[0] == -1);
        CHECK(-v[1] == -2);
        CHECK(-v[2] == -3);
    }

    SECTION("Binary operators") {
        PhyberVec3_int v({1, 2, 3});
        PhyberVec3_int u({4, 5, 6});
        PhyberVec3_int w({-1, -2, -3});

        CHECK(v == v);
        CHECK(v != u);
        CHECK(-v == w);
        CHECK(v == std::vector<int>({1, 2, 3}));
        CHECK(v != std::vector<int>({1, 2, 4}));
        CHECK(v != std::vector<int>({1, 2, 3, 4}));

        CHECK((v * 2) == std::vector<int>({2, 4, 6}));
        CHECK((v + 3) == std::vector<int>({4, 5, 6}));
        CHECK((v - 3) == std::vector<int>({-2, -1, 0}));

        CHECK((v * u) == 32);
        CHECK((v + u) == std::vector<int>({5, 7, 9}));
        CHECK((v - u) == std::vector<int>({-3, -3, -3}));
    }
}

TEST_CASE("vectors 4d", "[vectors4]") {
    SECTION("Basic initialization") {
        {
            PhyberVec4_int u;
            CHECK(u[0] == 0);
            CHECK(u[1] == 0);
            CHECK(u[2] == 0);
            CHECK(u[3] == 0);
        }

        {
            PhyberVec4_int v({1, 2, 3, 4});
            CHECK(v[0] == 1);
            CHECK(v[1] == 2);
            CHECK(v[2] == 3);
            CHECK(v[3] == 4);

            CHECK(v.x() == 1);
            CHECK(v.y() == 2);
            CHECK(v.z() == 3);
            CHECK(v.w() == 4);

            v[0] = 5;
            v[1] = 6;
            v[2] = 7;
            v[3] = 8;
            CHECK(v[0] == 5);
            CHECK(v[1] == 6);
            CHECK(v[2] == 7);
            CHECK(v[3] == 8);

            v.x() = 9;
            v.y() = 10;
            v.z() = 11;
            v.w() = 12;
            CHECK(v.x() == 9);
            CHECK(v.y() == 10);
            CHECK(v.z() == 11);
            CHECK(v.w() == 12);
        }
    }

    SECTION("Unary operations") {
        PhyberVec4_int v({1, 2, 3, 4});

        CHECK_THROWS(v[4]);
        CHECK_THAT(v.length(), Catch::Matchers::WithinRel(sqrt(1*1 + 2*2 + 3*3 + 4*4), 1e-6));
        CHECK(-v[0] == -1);
        CHECK(-v[1] == -2);
        CHECK(-v[2] == -3);
        CHECK(-v[3] == -4);
    }

    SECTION("Binary operators") {
        PhyberVec4_int v({1, 2, 3, 4});
        PhyberVec4_int u({5, 6, 7, 8});
        PhyberVec4_int w({-1, -2, -3, -4});

        CHECK(v == v);
        CHECK(v != u);
        CHECK(-v == w);
        CHECK(v == std::vector<int>({1, 2, 3, 4}));
        CHECK(v != std::vector<int>({1, 2, 3, 5}));
        CHECK(v != std::vector<int>({1, 2, 3, 4, 5}));

        CHECK((v * 2) == std::vector<int>({2, 4, 6, 8}));
        CHECK((v + 3) == std::vector<int>({4, 5, 6, 7}));
        CHECK((v - 3) == std::vector<int>({-2, -1, 0, 1}));

        CHECK((v * u) == 70);
        CHECK((v + u) == std::vector<int>({6, 8, 10, 12}));
        CHECK((v - u) == std::vector<int>({-4, -4, -4, -4}));
    }
}

TEST_CASE("matrices 2x2", "[matrices2x2]") {
    SECTION("Basic initialization") {
        {
            PhyberMat2x2_int m;
            CHECK(m(0,0) == 0);
            CHECK(m(0,1) == 0);
            CHECK(m(1,0) == 0);
            CHECK(m(1,1) == 0);
        }

        {
            PhyberMat2x2_int m({1, 2, 3, 4});
            CHECK(m(0,0) == 1);
            CHECK(m(0,1) == 2);
            CHECK(m(1,0) == 3);
            CHECK(m(1,1) == 4);

            m(1,0) = 10;
            CHECK(m(1,0) == 10);
        }
    }

    SECTION("Unary operations") {
        PhyberMat2x2_int m({1, 2, 3, 4});

        CHECK_THROWS(m(1,2));
        CHECK_THROWS(m(2,1));
        // CHECK(m.determinant() == -2);
        CHECK(-m(0,0) == -1.0);
        CHECK(-m(0,1) == -2.0);
        CHECK(-m(1,0) == -3.0);
        CHECK(-m(1,1) == -4.0);
        CHECK(m.t() == std::vector<int>({1, 3, 2, 4}));

        m = PhyberMat2x2_int({1, 1, 2, 2});
        CHECK(m == std::vector<int>({1, 1, 2, 2}));
        // CHECK(m.determinant() == 0);
    }

    SECTION("Binary operators") {
        PhyberMat2x2_int m({1, 2, 3, 4});
        PhyberMat2x2_int o({5, 6, 7, 8});
        PhyberMat2x2_int p({-1, -2, -3, -4});

        CHECK(m == m);
        CHECK(m != o);
        CHECK(-m == p);
        CHECK(m == std::vector<int>({1, 2, 3, 4}));
        CHECK(m != std::vector<int>({1, 2, 3, 5}));
        CHECK(m != std::vector<int>({1, 2, 3, 4, 5}));

        CHECK((m * 2) == std::vector<int>({2, 4, 6, 8}));
        CHECK((m + 3) == std::vector<int>({4, 5, 6, 7}));
        CHECK((m - 3) == std::vector<int>({-2, -1, 0, 1}));

        CHECK((m * o) == std::vector<int>({19, 22, 43, 50}));
        CHECK((m + o) == std::vector<int>({6, 8, 10, 12}));
        CHECK((m - o) == std::vector<int>({-4, -4, -4, -4}));
    }

    SECTION("matrix vector multiplication") {
        PhyberMat2x2_int m({1, 2, 3, 4});
        PhyberVec2_int v({5, 6});

        CHECK(m * v == std::vector<int>({17, 39}));
    }
}

TEST_CASE("matrices 3x3", "[matrices3x3]") {
    SECTION("Basic initialization") {
        {
            PhyberMat3x3_int m;
            for (int r = 0; r < 3; ++r)
                for (int c = 0; c < 3; ++c)
                    CHECK(m(r,c) == 0);
        }

        {
            PhyberMat3x3_int m({
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            });

            CHECK(m(0,0) == 1);
            CHECK(m(0,1) == 2);
            CHECK(m(0,2) == 3);
            CHECK(m(1,0) == 4);
            CHECK(m(1,1) == 5);
            CHECK(m(1,2) == 6);
            CHECK(m(2,0) == 7);
            CHECK(m(2,1) == 8);
            CHECK(m(2,2) == 9);

            m(2,1) = 20;
            CHECK(m(2,1) == 20);
        }
    }

    SECTION("Unary operations") {
        PhyberMat3x3_int m({
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        });

        CHECK_THROWS(m(3,0));
        CHECK_THROWS(m(0,3));

        CHECK(m.t() == std::vector<int>({
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        }));

        // CHECK(m.determinant() == 0);

        m = PhyberMat3x3_int({
            1, 2, 3,
            6, 4, 5,
            8, 9, 7
        });
        CHECK(m == std::vector<int>({
            1, 2, 3,
            6, 4, 5,
            8, 9, 7
        }));
        // CHECK(m.determinant() == 45);
    }

    SECTION("Binary operators") {
        PhyberMat3x3_int m({
            1,2,3,
            4,5,6,
            7,8,9
        });

        PhyberMat3x3_int o({
            9,8,7,
            6,5,4,
            3,2,1
        });

        CHECK(m == m);
        CHECK(m != o);

        CHECK((m + o) == std::vector<int>({
            10,10,10,
            10,10,10,
            10,10,10
        }));

        CHECK((m - o) == std::vector<int>({
            -8,-6,-4,
            -2,0,2,
            4,6,8
        }));

        CHECK((m * 2) == std::vector<int>({
            2,4,6,
            8,10,12,
            14,16,18
        }));

        CHECK((m * o) == std::vector<int>({
            30,24,18,
            84,69,54,
            138,114,90
        }));
    }

    SECTION("matrix vector multiplication") {
        PhyberMat3x3_int m({
            1,2,3,
            4,5,6,
            7,8,9
        });

        PhyberVec3_int v({1,2,3});

        CHECK(m * v == std::vector<int>({14, 32, 50}));
    }
}

TEST_CASE("matrices 4x4", "[matrices4x4]") {
    SECTION("Basic initialization") {
        {
            PhyberMat4x4_int m;
            for (int r = 0; r < 4; ++r)
                for (int c = 0; c < 4; ++c)
                    CHECK(m(r,c) == 0);
        }

        {
            PhyberMat4x4_int m({
                1,  2,  3,  4,
                5,  6,  7,  8,
                9, 10, 11, 12,
                13, 14, 15, 16
            });

            for (int i = 0, r = 0; r < 4; ++r)
                for (int c = 0; c < 4; ++c)
                    CHECK(m(r,c) == ++i);

            m(2,2) = 30;
            CHECK(m(2,2) == 30);
        }
    }

    SECTION("Unary operations") {
        PhyberMat4x4_int m({
            1,  2,  3,  4,
            5,  6,  7,  8,
            9, 10, 11, 12,
            13, 14, 15, 16
        });

        // CHECK(m.determinant() == 0);

        CHECK(m.t() == std::vector<int>({
            1, 5, 9, 13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16
        }));

        m = PhyberMat4x4({
            1, 2, 3, 4,
            8, 5, 6, 7,
            11, 12, 9, 10,
            14, 15, 16, 13
        });
        // CHECK(m.determinant() == -544);
    }

    SECTION("Binary operators") {
        PhyberMat4x4_int m({
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        });

        PhyberMat4x4_int o({
            16, 15, 14, 13,
            12, 11, 10, 9,
            8, 7, 6, 5,
            4, 3, 2, 1
        });

        CHECK((m * o) == std::vector<int>({
            80, 70, 60, 50,
            240, 214, 188, 162,
            400, 358, 316, 274,
            560, 502, 444, 386
        }));

        CHECK((m + o) == std::vector<int>({
            17, 17, 17, 17,
            17, 17, 17, 17,
            17, 17, 17, 17,
            17, 17, 17, 17
        }));

        CHECK((m * 2) == std::vector<int>({
            2, 4, 6, 8,
            10, 12, 14, 16,
            18, 20, 22, 24,
            26, 28, 30, 32
        }));

        CHECK((m - o) == std::vector<int>({
            -15, -13, -11, -9,
            -7, -5, -3, -1,
            1, 3, 5, 7,
            9, 11, 13, 15
        }));
    }

    SECTION("matrix vector multiplication") {
        PhyberMat4x4_int m({
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        });

        PhyberVec4_int v({1, 2, 3, 4});

        CHECK(m * v == std::vector<int>({
            30, 70, 110, 150
        }));
    }
}
