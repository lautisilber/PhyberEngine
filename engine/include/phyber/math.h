#ifndef PHYBER_ENGINE_PHY_MATH_H
#define PHYBER_ENGINE_PHY_MATH_H

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <stdint.h>
#include <stddef.h>
#include <concepts>
#include <algorithm>
#include <type_traits>
#include <utility>

#include "phyber/utils/defs.h"
#include "utils/defs.h"

namespace Phyber {

template <Arithmetic T, unsigned int N, std::unsigned_integral I, bool RANGE_CHECK>
class PhyberVecN_T {
protected:
    T _vec[N];

public:
    // Default constructor: initializes elements to zero
    PhyberVecN_T() {
        std::fill(_vec, _vec + N, T{});
    }

    // Variadic constructor for exactly N elements
    template <typename... Args>
        requires (sizeof...(Args) == N) &&
                 (std::conjunction_v<std::is_convertible<Args, T>...>)
    PhyberVecN_T(Args&&... args) : _vec{ static_cast<T>(args)... } {}

    T operator[](I i) const {
        if constexpr(RANGE_CHECK) {
            if (i >= N) throw std::runtime_error("Out of bounds");
        }
        return _vec[i];
    }
    T &operator[](I i) {
        if constexpr(RANGE_CHECK) {
            if (i >= N) throw std::runtime_error("Out of bounds");
        }
        return _vec[i];
    }
};

template <Arithmetic T, unsigned int N, std::unsigned_integral I, bool RANGE_CHECK>
class PhyberMatNxN_T {
protected:
    T _mat[N * N];

public:
    // Default constructor: initializes all elements to zero
    PhyberMatNxN_T() {
        std::fill(_mat, _mat + N * N, T{});
    }

    // Variadic constructor: accepts exactly N*N arguments
    template <typename... Args>
        requires (sizeof...(Args) == N * N) &&
                 (std::conjunction_v<std::is_convertible<Args, T>...>)
    PhyberMatNxN_T(Args&&... args) : _mat{ static_cast<T>(args)... } {}

    T &operator()(I r, I c) {
        if constexpr(RANGE_CHECK) {
            if (r * N + c >= N) throw std::runtime_error("Out of bounds");
        }
        return _mat[r * N + c];
    }

    const T &operator()(I r, I c) const {
        if constexpr(RANGE_CHECK) {
            if (r * N + c >= N) throw std::runtime_error("Out of bounds");
        }
        return _mat[r * N + c];
    }

    void fill(T scalar) {
        std::fill(_mat, _mat + (N*N), scalar);
    }

    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) {
        // same as (scalar*Identity) * this
        using V = decltype(std::declval<T&>() * std::declval<U&>());

        PhyberMatNxN_T<V, N, I, RANGE_CHECK> new_mat;
        for (I r = 0; r < N; ++r) {
            for (I c = 0; c < N; ++c) {
                new_mat(r, c) = scalar * (*this)(r, c);
            }
        }

        return new_mat;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &vec) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<V, N, K, RANGE_CHECK || RC2> new_vec;

        for (K r = 0; r < N; ++r) {
            V sum{};
            for (K c = 0; c < N; ++c) {
                sum += (*this)(r, c) * vec[c];
            }
            new_vec[r] = sum;
        }

        return new_vec;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberMatNxN_T<U, N, J, RC2> &mat) {
        // Source - https://stackoverflow.com/a/57464417
        // Posted by Jeremy Roman, modified by community. See post 'Timeline' for change history
        // Retrieved 2026-02-12, License - CC BY-SA 4.0

        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberMatNxN_T<V, N, K, RANGE_CHECK || RC2> new_mat;

        for (K r = 0; r < N; ++r) {
            for (K c = 0; c < N; ++c) {
                V sum{};
                for (K i = 0; i < N; i++) {
                    sum += (*this)(r, i) * mat(i, c);
                }
                new_mat(r, c) = sum;
            }
        }
        return new_mat;
    }
};

class PhyberVec2 : public PhyberVecN_T<float, 2, uint8_t, true> {
public:
    float &x() { return _vec[0]; }
    const float &x() const { return _vec[0]; }
    float &y() { return _vec[1]; }
    const float &y() const { return _vec[1]; }
};

class PhyberVec3 : public PhyberVecN_T<float, 3, uint8_t, true> {
public:
    float &x() { return _vec[0]; }
    const float &x() const { return _vec[0]; }
    float &y() { return _vec[1]; }
    const float &y() const { return _vec[1]; }
    float &z() { return _vec[2]; }
    const float &z() const { return _vec[2]; }
};

class PhyberVec4 : public PhyberVecN_T<float, 4, uint8_t, true> {
public:
    float &x() { return _vec[0]; }
    const float &x() const { return _vec[0]; }
    float &y() { return _vec[1]; }
    const float &y() const { return _vec[1]; }
    float &z() { return _vec[2]; }
    const float &z() const { return _vec[2]; }
    float &w() { return _vec[3]; }
    const float &w() const { return _vec[3]; }
};

class PhyberVec2_int : public PhyberVecN_T<int, 2, uint8_t, true> {
public:
    int &x() { return _vec[0]; }
    const int &x() const { return _vec[0]; }
    int &y() { return _vec[1]; }
    const int &y() const { return _vec[1]; }
};

class PhyberVec3_int : public PhyberVecN_T<int, 3, uint8_t, true> {
public:
    int &x() { return _vec[0]; }
    const int &x() const { return _vec[0]; }
    int &y() { return _vec[1]; }
    const int &y() const { return _vec[1]; }
    int &z() { return _vec[2]; }
    const int &z() const { return _vec[2]; }
};

class PhyberVec4_int : public PhyberVecN_T<int, 4, uint8_t, true> {
public:
    int &x() { return _vec[0]; }
    const int &x() const { return _vec[0]; }
    int &y() { return _vec[1]; }
    const int &y() const { return _vec[1]; }
    int &z() { return _vec[2]; }
    const int &z() const { return _vec[2]; }
    int &w() { return _vec[3]; }
    const int &w() const { return _vec[3]; }
};

class PhyberQuaternion : public PhyberVecN_T<float, 4, uint8_t, true> {
    float &a() { return _vec[0]; }
    const float &a() const { return _vec[0]; }
    float &b() { return _vec[1]; }
    const float &b() const { return _vec[1]; }
    float &c() { return _vec[2]; }
    const float &c() const { return _vec[2]; }
    float &d() { return _vec[3]; }
    const float &d() const { return _vec[3]; }
};



class PhyberMat2x2: public PhyberMatNxN_T<float, 2, uint8_t, true> {};
class PhyberMat3x3: public PhyberMatNxN_T<float, 3, uint8_t, true> {};
class PhyberMat4x4: public PhyberMatNxN_T<float, 4, uint8_t, true> {};
class PhyberMat2x2_int: public PhyberMatNxN_T<int, 2, uint8_t, true> {};
class PhyberMat3x3_int: public PhyberMatNxN_T<int, 3, uint8_t, true> {};
class PhyberMat4x4_int: public PhyberMatNxN_T<int, 4, uint8_t, true> {};

extern PhyberMat2x2 phyber_mat_mul_2x2(const PhyberMat2x2 *m1, const PhyberMat2x2 *m2);
extern PhyberMat3x3 phyber_mat_mul_3x3(const PhyberMat3x3 *m1, const PhyberMat3x3 *m2);
extern PhyberMat4x4 phyber_mat_mul_4x4(const PhyberMat4x4 *m1, const PhyberMat4x4 *m2);
extern void phyber_mat_mul_2x2_inplace(const PhyberMat2x2 *m1, PhyberMat2x2 *m2);
extern void phyber_mat_mul_3x3_inplace(const PhyberMat3x3 *m1, PhyberMat3x3 *m2);
extern void phyber_mat_mul_4x4_inplace(const PhyberMat4x4 *m1, PhyberMat4x4 *m2);


extern PhyberVec2 phyber_mat_vec_mul_2x2(const PhyberMat2x2 *m, const PhyberVec2 *v);
extern PhyberVec3 phyber_mat_vec_mul_3x3(const PhyberMat3x3 *m, const PhyberVec3 *v);
extern PhyberVec4 phyber_mat_vec_mul_4x4(const PhyberMat4x4 *m, const PhyberVec4 *v);
extern void phyber_mat_vec_mul_2x2_inplace(const PhyberMat2x2 *m, PhyberVec2 *v);
extern void phyber_mat_vec_mul_3x3_inplace(const PhyberMat3x3 *m, PhyberVec3 *v);
extern void phyber_mat_vec_mul_4x4_inplace(const PhyberMat4x4 *m, PhyberVec4 *v);

extern void phyber_vector_2d_translate(PhyberVec2 *vec, const PhyberVec2 *translation);
extern void phyber_vector_2d_rotate(PhyberVec2 *vec, float angle);
extern void phyber_vector_2d_scale(PhyberVec2 *vec, const PhyberVec2 *scale);

}

#endif /* PHYBER_ENGINE_PHY_MATH_H */
