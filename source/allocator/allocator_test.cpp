#include "allocator.hpp"

#include <gtest/gtest.h>

namespace
{

using allocator::BlockAllocator;

TEST(BlockAllocatorTest, ShouldAllocateMemoryWhenSingleElementRequested)
{
    // Arrange
    BlockAllocator<int, 10> alloc;

    // Act
    int* ptr = alloc.allocate(1);

    // Assert
    ASSERT_NE(ptr, nullptr);
}

TEST(BlockAllocatorTest, ShouldAllocateNewBlockWhenCurrentBlockFull)
{
    // Arrange
    BlockAllocator<int, 5> alloc;
    alloc.allocate(5);

    // Act
    int* ptr = alloc.allocate(1);

    // Assert
    ASSERT_NE(ptr, nullptr);
}

TEST(BlockAllocatorTest, ShouldHandleZeroAllocationWhenZeroRequested)
{
    // Arrange
    BlockAllocator<int, 10> alloc;

    // Act
    int* ptr = alloc.allocate(0);

    // Assert
    ASSERT_EQ(ptr, nullptr);
}

}  // namespace