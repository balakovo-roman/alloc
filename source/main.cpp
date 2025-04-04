#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>

#include "allocator/allocator.hpp"
#include "containers/forward_list.hpp"
#include "math/math.hpp"

constexpr std::size_t BlockSize = 10;

using PairType = std::pair<const int, int>;

template <typename T>
using CustomAllocator = allocator::BlockAllocator<T, BlockSize>;

template <typename Allocator = std::allocator<PairType>>
auto CreateMap()
{
    std::map<int, int, std::less<>, Allocator> map;

    for (const auto item : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
    {
        map.emplace_hint(map.end(), item, math::Factorial(item));
    }

    return map;
}

template <typename Allocator = std::allocator<int>>
auto CreateList()
{
    containers::ForwardList<int, Allocator> list;

    for (const auto item : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
    {
        list.emplace_front(item);
    }

    return list;
}

template <typename Container>
void Print(const Container& container)
{
    if constexpr (std::is_same_v<typename Container::value_type, PairType>)
    {
        for (const auto& [key, value] : container)
        {
            std::cout << key << ' ' << value << std::endl;
        }
    }
    else
    {
        for (const auto& item : container)
        {
            std::cout << item << std::endl;
        }
    }
}

int main()
{
    Print(CreateMap());
    Print(CreateMap<CustomAllocator<PairType>>());

    Print(CreateList());
    Print(CreateList<CustomAllocator<int>>());

    return 0;
}