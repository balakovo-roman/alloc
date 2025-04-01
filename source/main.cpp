#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>

#include "allocator/allocator.hpp"
#include "math/math.hpp"

constexpr std::size_t BlockSize = 10;
constexpr std::size_t ArraySize = BlockSize;

using ValueType = std::pair<const int, int>;
using CustomAllocator = allocator::BlockAllocator<ValueType, BlockSize>;

template <typename Allocator = std::allocator<ValueType>>
auto CreateMap(const std::array<int, ArraySize>& input)
{
    std::map<int, int, std::less<>, Allocator> map;

    for (const auto item : input)
    {
        map.emplace_hint(map.end(), item, math::Factorial(item));
    }

    return map;
}

template <typename Map>
void PrintMap(const Map& map)
{
    for (const auto& [key, value] : map)
    {
        std::cout << key << ' ' << value << std::endl;
    }
}

int main()
{
    std::array<int, ArraySize> input;
    std::iota(input.begin(), input.end(), 0U);

    PrintMap(CreateMap(input));
    PrintMap(CreateMap<CustomAllocator>(input));

    return 0;
}