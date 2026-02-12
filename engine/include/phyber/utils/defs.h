#ifndef PHYBER_ENGINE_UTILS_H
#define PHYBER_ENGINE_UTILS_H

#include <concepts>
#include <type_traits>

// A custom concept combining standard concepts
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Or using the older type trait (std::is_arithmetic_v)
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;
// std::is_arithmetic includes char and bool types

#endif /* PHYBER_ENGINE_UTILS_H */
