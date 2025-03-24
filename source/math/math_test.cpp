#include "math.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

namespace
{

TEST(FactorialTest, ShouldReturnOneWhenInputIsZero)
{
    // Arrange
    constexpr int input = 0;

    // Act
    constexpr int result = math::Factorial(input);

    // Assert
    EXPECT_THAT(result, ::testing::Eq(1));
}

TEST(FactorialTest, ShouldReturnOneWhenInputIsOne)
{
    // Arrange
    constexpr int input = 1;

    // Act
    constexpr int result = math::Factorial(input);

    // Assert
    EXPECT_THAT(result, ::testing::Eq(1));
}

TEST(FactorialTest, ShouldReturnCorrectValueWhenInputIsPositive)
{
    // Arrange
    constexpr int input = 5;

    // Act
    constexpr int result = math::Factorial(input);

    // Assert
    EXPECT_THAT(result, ::testing::Eq(120));
}

TEST(FactorialTest, ShouldCompileWhenUsedInConstexprContext)
{
    // Arrange, Act, Assert
    static_assert(math::Factorial(3) == 6,
                  "Factorial should work in compile-time");
}

}  // namespace