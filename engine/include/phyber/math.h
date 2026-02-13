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
#include <cmath>
#include <array>
#include <vector>

#include "phyber/utils/defs.h"

namespace Phyber {

template <Arithmetic T, size_t N, std::unsigned_integral I, bool RANGE_CHECK>
class PhyberVecN_T {
    static_assert(N > 0, "Vectors need to have positive dimensions");
protected:
    T _vec[N];

    template <Arithmetic U, size_t M, std::unsigned_integral J, bool RC2>
    friend class PhyberVecN_T;

public:
    // Default constructor: initializes elements to zero
    PhyberVecN_T() {
        std::fill(_vec, _vec + N, T{});
    }

    // initializer_list constructor
    PhyberVecN_T(std::initializer_list<T> list) {
        if (list.size() != N) {
            throw std::invalid_argument("Initializer list size must be N");
        }

        std::copy(list.begin(), list.end(), _vec);
    }

    // Converting constructor (different arithmetic types)
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    PhyberVecN_T(const PhyberVecN_T<U, N, J, RC2>& v) {
        for (I i = 0; i < N; ++i)
            _vec[i] = static_cast<T>(v._vec[i]);
    }

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

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    auto &operator=(const PhyberVecN_T<U, N, J, RC2> &v) {
        if constexpr(std::is_same_v<T, U>) {
            std::copy(v._vec, v._vec + N - 1, _vec);
        } else {
            for (I i = 0; i < N; ++i) {
                this->_vec[i] = static_cast<T>(v[i]);
            }
        }
        return *this;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberVecN_T<U, N, J, RC2> &v) const requires (N == 2) {
        return _vec[0] == v._vec[0] &&
               _vec[1] == v._vec[1];
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberVecN_T<U, N, J, RC2> &v) const requires (N == 3) {
        return _vec[0] == v._vec[0] &&
               _vec[1] == v._vec[1] &&
               _vec[2] == v._vec[2];
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberVecN_T<U, N, J, RC2> &v) const requires (N == 4) {
        return _vec[0] == v._vec[0] &&
               _vec[1] == v._vec[1] &&
               _vec[2] == v._vec[2] &&
               _vec[3] == v._vec[3];
    }

    template <Arithmetic U, size_t M, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberVecN_T<U, M, J, RC2> &v) const {
        if (N != M) return false;

        using K = std::common_type_t<I, J>;

        for (K i = 0; i < N; ++i) {
            if (this->_vec[i] != v._vec[i]) return false;
        }
        return true;
    }

    template <Arithmetic U>
    bool operator==(std::vector<U> l) const requires(N == 2) {
        if (N != l.size()) return false;
        return _vec[0] == l[0] &&
               _vec[1] == l[1];
    }

    template <Arithmetic U>
    bool operator==(std::vector<U> l) const requires(N == 3) {
        if (N != l.size()) return false;
        return _vec[0] == l[0] &&
               _vec[1] == l[1] &&
               _vec[2] == l[2];
    }

    template <Arithmetic U>
    bool operator==(std::vector<U> l) const requires(N == 4) {
        if (N != l.size()) return false;
        return _vec[0] == l[0] &&
               _vec[1] == l[1] &&
               _vec[2] == l[2] &&
               _vec[3] == l[3];
    }

    template <Arithmetic U>
    bool operator==(std::vector<U> l) const {
        if (N != l.size()) return false;

        for (I i = 0; i < N; ++i) {
            if (this->_vec[i] != l[i]) return false;
        }
        return true;
    }

    template <Arithmetic U>
    bool operator==(std::array<U, N> l) const requires(N == 2) {
        return _vec[0] == l[0] &&
               _vec[1] == l[1];
    }

    template <Arithmetic U>
    bool operator==(std::array<U, N> l) const requires(N == 3) {
        return _vec[0] == l[0] &&
               _vec[1] == l[1] &&
               _vec[2] == l[2];
    }

    template <Arithmetic U>
    bool operator==(std::array<U, N> l) const requires(N == 4) {
        return _vec[0] == l[0] &&
               _vec[1] == l[1] &&
               _vec[2] == l[2] &&
               _vec[3] == l[3];
    }

    template <Arithmetic U, size_t M>
    bool operator==(std::array<U, M> l) const {
        if (N != M) return false;

        for (I i = 0; i < N; ++i) {
            if (this->_vec[i] != l[i]) return false;
        }
        return true;
    }

    auto length() const requires (N == 2) {
        return std::sqrt(_vec[0]*_vec[0] + _vec[1]*_vec[1]);
    }
    auto length() const requires (N == 3) {
        return std::sqrt(_vec[0]*_vec[0] + _vec[1]*_vec[1] + _vec[2]*_vec[2]);
    }
    auto length() const requires (N == 4) {
        return std::sqrt(_vec[0]*_vec[0] + _vec[1]*_vec[1] + _vec[2]*_vec[2] + _vec[3]*_vec[3]);
    }

    auto length() const {
        using U = std::common_type_t<T, float>;

        U sum{};
        for (I i = 0; i < N; ++i) {
            sum += this->_vec[i] * this->_vec[i];
        }

        return std::sqrt(sum);
    }
    inline auto magnitude() const { return length(); }

    [[nodiscard]] auto operator-() const requires(N == 2) {
        PhyberVecN_T<T, N, I, RANGE_CHECK> v({-_vec[0], -_vec[1]});
        return v;
    }
    [[nodiscard]] auto operator-() const requires(N == 3) {
        PhyberVecN_T<T, N, I, RANGE_CHECK> v({-_vec[0], -_vec[1], -_vec[2]});
        return v;
    }
    [[nodiscard]] auto operator-() const requires(N == 4) {
        PhyberVecN_T<T, N, I, RANGE_CHECK> v({-_vec[0], -_vec[1], -_vec[2], -_vec[4]});
        return v;
    }
    [[nodiscard]] auto operator-() const {
        PhyberVecN_T<T, N, I, RANGE_CHECK> v;
        for (I i = 0; i < N; ++i) {
            v._vec[i] = -_vec[i];
        }
        return v;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 2) {
        return _vec[0]*v->_vec[0] + _vec[1]*v->_vec[1];
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 3) {
        return _vec[0]*v->_vec[0] + _vec[1]*v->_vec[1] + _vec[2]*v->_vec[2];
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 4) {
        return _vec[0]*v->_vec[0] + _vec[1]*v->_vec[1] + _vec[2]*v->_vec[2] + _vec[3]*v->_vec[3];
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &v) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;

        V sum{};
        for (K i = 0; i < N; ++i) {
            sum += this->_vec[i] * v._vec[i];
        }

        return sum;
    }


    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 2) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]*scalar, _vec[1]*scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 3) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]*scalar, _vec[1]*scalar, _vec[2]*scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 4) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]*scalar, _vec[1]*scalar, _vec[2]*scalar, _vec[3]*scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const {
        using V = decltype(std::declval<T&>() * std::declval<U&>());

        PhyberVecN_T<V, N, I, RANGE_CHECK> v;
        for (I i = 0; i < N; ++i) {
            v[i] = this->_vec[i] * scalar;
        }

        return v;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 2) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, K, RANGE_CHECK | RC2> u({_vec[0]+v._vec[0], _vec[1]+v._vec[1]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 3) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, K, RANGE_CHECK | RC2> u({_vec[0]+v._vec[0], _vec[1]+v._vec[1], _vec[2]+v._vec[2]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 4) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, K, RANGE_CHECK | RC2> u({_vec[0]+v._vec[0], _vec[1]+v._vec[1], _vec[2]+v._vec[2], _vec[4]+v._vec[4]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberVecN_T<U, N, J, RC2> &v) const {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberVecN_T<U, N, J, RANGE_CHECK | RC2> u;
        for (K i = 0; i < N; ++i) {
            u[i] = this->_vec[i] + v._vec[i];
        }

        return u;
    }


    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 2) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]+scalar, _vec[1]+scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 3) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]+scalar, _vec[1]+scalar, _vec[2]+scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 4) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]+scalar, _vec[1]+scalar, _vec[2]+scalar, _vec[3]+scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const {
        using V = decltype(std::declval<T&>() + std::declval<U&>());

        PhyberVecN_T<V, N, I, RANGE_CHECK> v;
        for (I i = 0; i < N; ++i) {
            v[i] = this->_vec[i] + scalar;
        }

        return v;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 2) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, J, RANGE_CHECK | RC2> u({_vec[0]-v._vec[0], _vec[1]-v._vec[1]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 3) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, J, RANGE_CHECK | RC2> u({_vec[0]-v._vec[0], _vec[1]-v._vec[1], _vec[2]-v._vec[2]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberVecN_T<U, N, J, RC2> &v) const requires(N == 4) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<U, N, J, RANGE_CHECK | RC2> u({_vec[0]-v._vec[0], _vec[1]-v._vec[1], _vec[2]-v._vec[2], _vec[3]-v._vec[3]});
        return u;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberVecN_T<U, N, J, RC2> &v) const {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberVecN_T<U, N, K, RANGE_CHECK | RC2> u;
        for (K i = 0; i < N; ++i) {
            u[i] = this->_vec[i] - v._vec[i];
        }

        return u;
    }


    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 2) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]-scalar, _vec[1]-scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 3) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]-scalar, _vec[1]-scalar, _vec[2]-scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 4) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberVecN_T<V, N, I, RANGE_CHECK> v({_vec[0]-scalar, _vec[1]-scalar, _vec[2]-scalar, _vec[3]-scalar});
        return v;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const {
        using V = decltype(std::declval<T&>() - std::declval<U&>());

        PhyberVecN_T<V, N, I, RANGE_CHECK> v;
        for (I i = 0; i < N; ++i) {
            v[i] = this->_vec[i] - scalar;
        }

        return v;
    }

    void swap(I i, I j) {
        if constexpr(RANGE_CHECK) {
            if (i >= N || j >= N) {
                throw std::runtime_error("Out of bounds");
            }
        }
        std::swap(_vec + i, _vec + j);
    }

    // x()
    T& x() requires (N >= 1 && N <= 4) { return _vec[0]; }
    const T& x() const requires (N >= 1 && N <= 4) { return _vec[0]; }

    // y()
    T& y() requires (N >= 2 && N <= 4) { return _vec[1]; }
    const T& y() const requires (N >= 2 && N <= 4) { return _vec[1]; }

    // z()
    T& z() requires (N >= 3 && N <= 4) { return _vec[2]; }
    const T& z() const requires (N >= 3 && N <= 4) { return _vec[2]; }

    // w()
    T& w() requires (N >= 4 && N <= 4) { return _vec[3]; }
    const T& w() const requires (N >= 4 && N <= 4) { return _vec[3]; }
};

template <Arithmetic T, size_t N, std::unsigned_integral I, bool RANGE_CHECK>
class PhyberMatNxN_T {
    static_assert(N > 0, "Matrix needs to have positive dimensions");
protected:
    T _mat[N * N];

    template <Arithmetic U, size_t M, std::unsigned_integral J, bool RC2>
    friend class PhyberMatNxN_T;  // ← this allows any PhyberMatNxN_T<U, M, J, RC2> to access _mat

public:
    // Default constructor: initializes all elements to zero
    PhyberMatNxN_T() {
        std::fill(_mat, _mat + N * N, T{});
    }

    // initializer_list constructor
    PhyberMatNxN_T(std::initializer_list<T> list) {
        if (list.size() != N * N) {
            throw std::invalid_argument("Initializer list size must be N*N");
        }
        std::copy(list.begin(), list.end(), _mat);
    }

    // Converting constructor (different arithmetic types)
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    PhyberMatNxN_T(const PhyberMatNxN_T<U, N, J, RC2>& m) {
        for (I i = 0; i < N*N; ++i) {
            _mat[i] = static_cast<T>(m._mat[i]);
        }
    }

    T &operator()(I r, I c) {
        if constexpr(RANGE_CHECK) {
            if (r >= N || c >= N) throw std::runtime_error("Out of bounds");
        }
        return _mat[r * N + c];
    }

    const T &operator()(I r, I c) const {
        if constexpr(RANGE_CHECK) {
            if (r >= N || c >= N) throw std::runtime_error("Out of bounds");
        }
        return _mat[r * N + c];
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    auto &operator=(const PhyberMatNxN_T<U, N, J, RC2> &m) {
        if constexpr(std::is_same_v<T, U>) {
            std::copy(m._mat, m._mat + (N*N) - 1, _mat);
        } else {
            for (I i = 0; i < N*N; ++i) {
                (*this)._mat[i] = static_cast<T>(m._mat[i]);
            }
        }
        return *this;
    }

    void fill(T scalar) {
        std::fill(_mat, _mat + (N*N), scalar);
    }

    void swap(I r1, I c1, I r2, I c2) {
        if constexpr(RANGE_CHECK) {
            if ((r1 * N + c1 >= N) || (r2 * N + c2 >= N)) {
                throw std::runtime_error("Out of bounds");
            }
        }
        std::swap(_mat + r1 * N + c1, _mat + r2 * N + c2);
    }

    [[nodiscard]] auto operator-() const requires(N == 2) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> m({
            -_mat[0], -_mat[1],
            -_mat[2], -_mat[3]
        });
        return m;
    }
    [[nodiscard]] auto operator-() const requires(N == 3) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> m({
            -_mat[0], -_mat[1], -_mat[2],
            -_mat[3], -_mat[4], -_mat[5],
            -_mat[6], -_mat[7], -_mat[8]
        });
        return m;
    }
    [[nodiscard]] auto operator-() const requires(N == 4) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> m({
            -_mat[0], -_mat[1], -_mat[2], -_mat[3],
            -_mat[4], -_mat[5], -_mat[6], -_mat[7],
            -_mat[8], -_mat[9], -_mat[10], -_mat[11],
            -_mat[12], -_mat[13], -_mat[14], -_mat[15]
        });
        return m;
    }
    [[nodiscard]] auto operator-() const {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> m;
        for (I i = 0; i < N*N; ++i) {
            m._mat[i] = -_mat[i];
        }
        return m;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 2) {
        return _mat[0] == m._mat[0] &&
               _mat[1] == m._mat[1];
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 3) {
        return _mat[0] == m._mat[0] &&
               _mat[1] == m._mat[1] &&
               _mat[2] == m._mat[2];
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 4) {
        return _mat[0] == m._mat[0] &&
               _mat[1] == m._mat[1] &&
               _mat[2] == m._mat[2] &&
               _mat[3] == m._mat[3];
    }
    template <Arithmetic U, size_t M, std::unsigned_integral J, bool RC2>
    bool operator==(const PhyberMatNxN_T<U, M, J, RC2> &m) const {
        if (N != M) return false;

        using K = std::common_type_t<I, J>;

        for (K i = 0; i < N * N; ++i) {
            if (this->_mat[i] != m._mat[i]) return false;
        }
        return true;
    }

    template <Arithmetic U>
    bool operator==(const std::vector<U> &m) const {
        if (N * N != m.size()) return false;

        for (I i = 0; i < N * N; ++i) {
            if (this->_mat[i] != m[i]) return false;
        }
        return true;
    }

    template <Arithmetic U, size_t M>
    bool operator==(const std::array<U, M> &m) const {
        if (N * N != m.size()) return false;

        for (I i = 0; i < N * N; ++i) {
            if (this->_mat[i] != m[i]) return false;
        }
        return true;
    }

    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 2) {
        // same as (scalar*Identity) * this
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> new_mat({(*this)(0,0) * scalar, (*this)(0,1) * scalar,
                                                      (*this)(1,0) * scalar, (*this)(1,1) * scalar});
        return new_mat;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 3) {
        // same as (scalar*Identity) * this
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> new_mat({(*this)(0,0) * scalar, (*this)(0,1) * scalar, (*this)(0,2) * scalar,
                                                      (*this)(1,0) * scalar, (*this)(1,1) * scalar, (*this)(1,2) * scalar,
                                                      (*this)(2,0) * scalar, (*this)(2,1) * scalar, (*this)(2,2) * scalar});
        return new_mat;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const requires(N == 4) {
        // same as (scalar*Identity) * this
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> new_mat({(*this)(0,0) * scalar, (*this)(0,1) * scalar, (*this)(0,2) * scalar, (*this)(0,3) * scalar,
                                                      (*this)(1,0) * scalar, (*this)(1,1) * scalar, (*this)(1,2) * scalar, (*this)(0,3) * scalar,
                                                      (*this)(2,0) * scalar, (*this)(2,1) * scalar, (*this)(2,2) * scalar, (*this)(2,3) * scalar,
                                                      (*this)(3,0) * scalar, (*this)(3,1) * scalar, (*this)(3,2) * scalar, (*this)(3,3) * scalar});
        return new_mat;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator*(const U &scalar) const {
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
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &vec) const requires(N == 2) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<V, N, K, RANGE_CHECK || RC2> new_vec({
            (*this)(0,0) * vec[0] + (*this)(0,1) * vec[1],
            (*this)(1,0) * vec[0] + (*this)(1,1) * vec[1]
        });

        return new_vec;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &vec) const requires(N == 3) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<V, N, K, RANGE_CHECK || RC2> new_vec({
            (*this)(0,0) * vec[0] + (*this)(0,1) * vec[1] + (*this)(0,2) * vec[2],
            (*this)(1,0) * vec[0] + (*this)(1,1) * vec[1] + (*this)(1,2) * vec[2],
            (*this)(2,0) * vec[0] + (*this)(2,1) * vec[1] + (*this)(2,2) * vec[2]
        });

        return new_vec;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &vec) const requires(N == 4) {
        using V = decltype(std::declval<T&>() * std::declval<U&>());
        using K = std::common_type_t<I, J>;
        PhyberVecN_T<V, N, K, RANGE_CHECK || RC2> new_vec({
            (*this)(0,0) * vec[0] + (*this)(0,1) * vec[1] + (*this)(0,2) * vec[2] + (*this)(0,3) * vec[3],
            (*this)(1,0) * vec[0] + (*this)(1,1) * vec[1] + (*this)(1,2) * vec[2] + (*this)(1,3) * vec[3],
            (*this)(2,0) * vec[0] + (*this)(2,1) * vec[1] + (*this)(2,2) * vec[2] + (*this)(2,3) * vec[3],
            (*this)(3,0) * vec[0] + (*this)(3,1) * vec[1] + (*this)(3,2) * vec[2] + (*this)(3,3) * vec[3]
        });

        return new_vec;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator*(const PhyberVecN_T<U, N, J, RC2> &vec) const {
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
    [[nodiscard]] auto operator*(const PhyberMatNxN_T<U, N, J, RC2> &mat) const {
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

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 2) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] + m._mat[0], _mat[1] + m._mat[1],
            _mat[2] + m._mat[2], _mat[3] + m._mat[3]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 3) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] + m._mat[0], _mat[1] + m._mat[1], _mat[2] + m._mat[2],
            _mat[3] + m._mat[3], _mat[4] + m._mat[4], _mat[5] + m._mat[5],
            _mat[6] + m._mat[6], _mat[7] + m._mat[7], _mat[8] + m._mat[8]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 4) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] + m._mat[0], _mat[1] + m._mat[1], _mat[2] + m._mat[2], _mat[3] + m._mat[3],
            _mat[4] + m._mat[4], _mat[5] + m._mat[5], _mat[6] + m._mat[6], _mat[7] + m._mat[7],
            _mat[8] + m._mat[8], _mat[9] + m._mat[9], _mat[10] + m._mat[10], _mat[11] + m._mat[11],
            _mat[12] + m._mat[12], _mat[13] + m._mat[13], _mat[14] + m._mat[14], _mat[15] + m._mat[15]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator+(const PhyberMatNxN_T<U, N, J, RC2> &m) const {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out;

        for (K i = 0; i < N * N; ++i) {
            out._mat[i] = _mat[i] + m._mat[i];
        }

        return out;
    }

    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 2) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] + scalar, _mat[1] + scalar,
            _mat[2] + scalar, _mat[3] + scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 3) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] + scalar, _mat[1] + scalar, _mat[2] + scalar,
            _mat[3] + scalar, _mat[4] + scalar, _mat[5] + scalar,
            _mat[6] + scalar, _mat[7] + scalar, _mat[8] + scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const requires(N == 4) {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] + scalar, _mat[1] + scalar, _mat[2] + scalar, _mat[3] + scalar,
            _mat[4] + scalar, _mat[5] + scalar, _mat[6] + scalar, _mat[7] + scalar,
            _mat[8] + scalar, _mat[9] + scalar, _mat[10] + scalar, _mat[11] + scalar,
            _mat[12] + scalar, _mat[13] + scalar, _mat[14] + scalar, _mat[15] + scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator+(const U &scalar) const {
        using V = decltype(std::declval<T&>() + std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m;

        for (I i = 0; i < N * N; ++i) {
            m._mat[i] = _mat[i] + scalar;
        }

        return m;
    }

    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 2) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] - m._mat[0], _mat[1] - m._mat[1],
            _mat[2] - m._mat[2], _mat[3] - m._mat[3]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 3) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] - m._mat[0], _mat[1] - m._mat[1], _mat[2] - m._mat[2],
            _mat[3] - m._mat[3], _mat[4] - m._mat[4], _mat[5] - m._mat[5],
            _mat[6] - m._mat[6], _mat[7] - m._mat[7], _mat[8] - m._mat[8]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberMatNxN_T<U, N, J, RC2> &m) const requires(N == 4) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out({
            _mat[0] - m._mat[0], _mat[1] - m._mat[1], _mat[2] - m._mat[2], _mat[3] - m._mat[3],
            _mat[4] - m._mat[4], _mat[5] - m._mat[5], _mat[6] - m._mat[6], _mat[7] - m._mat[7],
            _mat[8] - m._mat[8], _mat[9] - m._mat[9], _mat[10] - m._mat[10], _mat[11] - m._mat[11],
            _mat[12] - m._mat[12], _mat[13] - m._mat[13], _mat[14] - m._mat[14], _mat[15] - m._mat[15]
        });

        return out;
    }
    template <Arithmetic U, std::unsigned_integral J, bool RC2>
    [[nodiscard]] auto operator-(const PhyberMatNxN_T<U, N, J, RC2> &m) const {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        using K = std::common_type_t<I, J>;

        PhyberMatNxN_T<V, N, K, RANGE_CHECK | RC2> out;

        for (K i = 0; i < N * N; ++i) {
            out._mat[i] = _mat[i] - m._mat[i];
        }

        return out;
    }

    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 2) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] - scalar, _mat[1] - scalar,
            _mat[2] - scalar, _mat[3] - scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 3) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] - scalar, _mat[1] - scalar, _mat[2] - scalar,
            _mat[3] - scalar, _mat[4] - scalar, _mat[5] - scalar,
            _mat[6] - scalar, _mat[7] - scalar, _mat[8] - scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const requires(N == 4) {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m({
            _mat[0] - scalar, _mat[1] - scalar, _mat[2] - scalar, _mat[3] - scalar,
            _mat[4] - scalar, _mat[5] - scalar, _mat[6] - scalar, _mat[7] - scalar,
            _mat[8] - scalar, _mat[9] - scalar, _mat[10] - scalar, _mat[11] - scalar,
            _mat[12] - scalar, _mat[13] - scalar, _mat[14] - scalar, _mat[15] - scalar
        });
        return m;
    }
    template <Arithmetic U>
    [[nodiscard]] auto operator-(const U &scalar) const {
        using V = decltype(std::declval<T&>() - std::declval<U&>());
        PhyberMatNxN_T<V, N, I, RANGE_CHECK> m;

        for (I i = 0; i < N * N; ++i) {
            m._mat[i] = _mat[i] - scalar;
        }

        return m;
    }

    void t_inline() {
        for (I r = 0; r < N; ++r) {
            for (I c = r + 1; c < N; ++c) {
                std::swap((*this)(r,c), (*this)(c,r));
            }
        }
    }
    [[nodiscard]] PhyberMatNxN_T<T, N, I, RANGE_CHECK> t() const requires(N == 2) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> out({
            (*this)(0,0), (*this)(1,0),
            (*this)(0,1), (*this)(1,1)
        });
        return out;
    }
    [[nodiscard]] PhyberMatNxN_T<T, N, I, RANGE_CHECK> t() const requires(N == 3) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> out({
            (*this)(0,0), (*this)(1,0), (*this)(2,0),
            (*this)(0,1), (*this)(1,1), (*this)(2,1),
            (*this)(0,2), (*this)(1,2), (*this)(2,2)
        });
        return out;
    }
    [[nodiscard]] PhyberMatNxN_T<T, N, I, RANGE_CHECK> t() const requires(N == 4) {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> out({
            (*this)(0,0), (*this)(1,0), (*this)(2,0), (*this)(3,0),
            (*this)(0,1), (*this)(1,1), (*this)(2,1), (*this)(3,1),
            (*this)(0,2), (*this)(1,2), (*this)(2,2), (*this)(3,2),
            (*this)(0,3), (*this)(1,3), (*this)(2,3), (*this)(3,3)
        });
        return out;
    }
    [[nodiscard]] PhyberMatNxN_T<T, N, I, RANGE_CHECK> t() const {
        PhyberMatNxN_T<T, N, I, RANGE_CHECK> out = *this;
        out.t_inline();
        return out;
    }

    [[nodiscard]] T determinant() const requires(N == 2) {
        return (*this)(0,0) * (*this)(1,1) - (*this)(0,1) * (*this)(1,0);
    }
    [[nodiscard]] T determinant() const {
        return _determinant_impl(*this);
    }

private:
    // Helper function
    template<size_t M>
    [[nodiscard]] static T _determinant_impl(const PhyberMatNxN_T<T, M, I, RANGE_CHECK> &mat) {
        if constexpr(N == 1) { return mat(0,0); }
        else if constexpr(N == 2) {
            return mat(0,0) * mat(1,1) - mat(0,1) * mat(1,0);
        }

        T res{};
        for (I c = 0; c < N; ++c) {
            // Build submatrix by skipping row 0 and column 'col'
            PhyberMatNxN_T<T, N-1, I, RANGE_CHECK> sub;
            for (I i = 1; i < N; ++i) {
                I subcol = 0;
                for (I j = 0; j < N; ++j) {
                    if (j == c) continue;
                    sub(i-1, subcol++) = mat(i,j);
                }
            }

            T sign = (c % 2 == 0) ? T(1) : T(-1);
            res += sign * mat(0, c) * _determinant_impl(sub);
        }

        return res;
    }
};

using PhyberVec2 = PhyberVecN_T<float, 2, uint8_t, true>;
using PhyberVec3 = PhyberVecN_T<float, 3, uint8_t, true>;
using PhyberVec4 = PhyberVecN_T<float, 4, uint8_t, true>;
using PhyberVec2_int = PhyberVecN_T<int, 2, uint8_t, true>;
using PhyberVec3_int = PhyberVecN_T<int, 3, uint8_t, true>;
using PhyberVec4_int = PhyberVecN_T<int, 4, uint8_t, true>;

using PhyberMat2x2 = PhyberMatNxN_T<float, 2, uint8_t, true>;
using PhyberMat3x3 = PhyberMatNxN_T<float, 3, uint8_t, true>;
using PhyberMat4x4 = PhyberMatNxN_T<float, 4, uint8_t, true>;
using PhyberMat2x2_int = PhyberMatNxN_T<int, 2, uint8_t, true>;
using PhyberMat3x3_int = PhyberMatNxN_T<int, 3, uint8_t, true>;
using PhyberMat4x4_int = PhyberMatNxN_T<int, 4, uint8_t, true>;

extern PhyberMat2x2 matrix_rotation_2d(float radians);

}

#endif /* PHYBER_ENGINE_PHY_MATH_H */
