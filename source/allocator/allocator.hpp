#include <cstddef>
#include <deque>
#include <memory>

#include "logger.hpp"

namespace allocator
{

template <typename T, std::size_t BlockSize>
class BlockAllocator
{
   public:
    using value_type = T;

    template <typename U>
    struct rebind
    {
        using other = BlockAllocator<U, BlockSize>;
    };

    BlockAllocator() = default;
    BlockAllocator(const BlockAllocator&) = delete;
    BlockAllocator(BlockAllocator&&) noexcept = default;
    BlockAllocator& operator=(const BlockAllocator&) = delete;
    BlockAllocator& operator=(BlockAllocator&&) noexcept = default;
    ~BlockAllocator();

    T* allocate(std::size_t count);
    void deallocate(T* p, std::size_t n) noexcept;

   private:
    T* AllocateNewBlock(std::size_t count);
    void CalculateNewCapacity(std::size_t count);
    bool IsExceedCapacity(std::size_t count) const noexcept;

    std::deque<std::unique_ptr<T[]>> blocks_;
    T* current_block_{};
    std::size_t used_{};
    std::size_t capacity_{};
};

template <typename T, std::size_t BlockSize>
BlockAllocator<T, BlockSize>::~BlockAllocator()
{
    LOG("Total blocks allocated: ", blocks_.size());
}

template <typename T, std::size_t BlockSize>
T* BlockAllocator<T, BlockSize>::allocate(std::size_t count)
{
    LOG("Request to allocate ", count, " elements");

    if (IsExceedCapacity(count))
    {
        LOG("Not enough space in current block (used: ", used_,
            ", capacity: ", capacity_, ")");
        CalculateNewCapacity(count);
        current_block_ = AllocateNewBlock(capacity_);
        used_ = 0;
        LOG("New block allocated at ", static_cast<void*>(current_block_));
    }

    T* result = current_block_ + used_;
    used_ += count;

    LOG("Allocation successful at ", static_cast<void*>(result),
        ", remaining in current block: ", capacity_ - used_);

    return result;
}

template <typename T, std::size_t BlockSize>
void BlockAllocator<T, BlockSize>::deallocate(
    [[maybe_unused]] T* p, [[maybe_unused]] std::size_t n) noexcept
{
    LOG("Deallocation called for ", n, " elements at ", static_cast<void*>(p));
}

template <typename T, std::size_t BlockSize>
T* BlockAllocator<T, BlockSize>::AllocateNewBlock(std::size_t count)
{
    return blocks_.emplace_back(std::make_unique<T[]>(count)).get();
}

template <typename T, std::size_t BlockSize>
void BlockAllocator<T, BlockSize>::CalculateNewCapacity(std::size_t count)
{
    while (used_ + count > capacity_)
    {
        capacity_ += BlockSize;
    }

    LOG("New capacity: ", capacity_);
}

template <typename T, std::size_t BlockSize>
bool BlockAllocator<T, BlockSize>::IsExceedCapacity(
    std::size_t count) const noexcept
{
    return used_ + count > capacity_;
}

}  // namespace allocator
