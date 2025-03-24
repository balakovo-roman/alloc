#pragma once

#include <type_traits>

namespace math
{

template <typename T>
constexpr T Factorial(T n)
{
    static_assert(std::is_integral_v<T>,
                  "Factorial is only defined for integral types");
    return (n <= 1) ? 1 : (n * Factorial(n - 1));
}

}  // namespace math
