#pragma once

#include <memory>

namespace containers
{

template <typename T, typename Allocator = std::allocator<T>>
class ForwardList final
{
   public:
    template <typename ValueType>
    class Iterator;

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using value_type = T;

    ForwardList() noexcept;
    explicit ForwardList(const Allocator& alloc) noexcept;
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other) noexcept;
    ~ForwardList();

    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other) noexcept;

    bool empty() const noexcept;
    void clear() noexcept;

    template <typename... Args>
    void emplace_front(Args&&... args);
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();

    iterator insert_after(iterator pos, const T& value);

    void reverse();

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

   private:
    struct Node;

    using NodeAllocator =
        typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    Node* head;
    NodeAllocator alloc;
};

}  // namespace containers

#include "forward_list.ipp"