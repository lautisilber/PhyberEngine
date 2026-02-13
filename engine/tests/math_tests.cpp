#include "phyber/math.h"
#include <cmath>
#include <cstdint>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Phyber;

namespace Catch {
    template <typename T, unsigned int N, std::unsigned_integral I, bool RANGE_CHECK>
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

    template <typename T, unsigned int N, std::unsigned_integral I, bool RANGE_CHECK>
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

TEST_CASE("vectors behave correctly", "[vectors]") {
    SECTION("Basic initialization") {
        {
            PhyberVecN_T<int, 3, uint8_t, true> u;
            CHECK(u[0] == 0);
            CHECK(u[1] == 0);
            CHECK(u[2] == 0);
        }

        {
            PhyberVecN_T<int, 3, uint8_t, true> v({1, 2, 3});
            CHECK(v[0] == 1);
            CHECK(v[1] == 2);
            CHECK(v[2] == 3);
        }
    }

    SECTION("Unary operations") {
        PhyberVecN_T<float, 3, uint8_t, true> v({1, 2, 3});

        CHECK_THROWS(v[3]);
        CHECK_THAT(v.length(), Catch::Matchers::WithinRel(sqrt(14), 1e-6));
        CHECK(-v[0] == -1.0);
        CHECK(-v[1] == -2.0);
        CHECK(-v[2] == -3.0);
    }

    SECTION("Binary operators") {
        PhyberVecN_T<int, 3, uint8_t, true> v({1, 2, 3});
        PhyberVecN_T<int, 3, uint8_t, true> u({4, 5, 6});
        PhyberVecN_T<int, 3, uint8_t, true> w({-1, -2, -3});

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

TEST_CASE("matrices behave correctly", "[matrices]") {
    SECTION("Basic initialization") {
        {
            Phyber::PhyberMatNxN_T<int, 2, uint8_t, true> m;
            CHECK(m(0,0) == 0);
            CHECK(m(0,1) == 0);
            CHECK(m(1,0) == 0);
            CHECK(m(1,1) == 0);
        }

        {
            Phyber::PhyberMatNxN_T<int, 2, uint8_t, true> m({1, 2, 3, 4});
            CHECK(m(0,0) == 1);
            CHECK(m(0,1) == 2);
            CHECK(m(1,0) == 3);
            CHECK(m(1,1) == 4);
        }

        {
            Phyber::PhyberMatNxN_T<int, 2, uint8_t, true> m({1, 2, 3, 4});
            CHECK(m(0,0) == 1);
            CHECK(m(0,1) == 2);
            CHECK(m(1,0) == 3);
            CHECK(m(1,1) == 4);
        }
    }

    SECTION("Unary operations") {
        Phyber::PhyberMatNxN_T<int, 2, uint8_t, true> m({1, 2, 3, 4});

        CHECK_THROWS(m(1,2));
        CHECK_THROWS(m(2,1));
        CHECK(m.determinant() == -2);
        CHECK(-m(0,0) == -1.0);
        CHECK(-m(0,1) == -2.0);
        CHECK(-m(1,0) == -3.0);
        CHECK(-m(1,1) == -4.0);
        CHECK(m.t() == std::vector<int>({1, 3, 2, 4}));
    }

    SECTION("Binary operators") {
        PhyberMatNxN_T<int, 2, uint8_t, true> m({1, 2, 3, 4});
        PhyberMatNxN_T<int, 2, uint8_t, true> o({5, 6, 7, 8});
        PhyberMatNxN_T<int, 2, uint8_t, true> p({-1, -2, -3, -4});

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
        PhyberMat3x3_int m({1, 2, 3, 4, 5, 6, 7, 8, 9});
        PhyberVec3_int v({10, 11, 12});

        CHECK(m * v == std::vector<int>({68, 167, 266}));
    }
}
