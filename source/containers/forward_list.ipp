#include "forward_list.hpp"
#include "logger.hpp"

namespace containers
{

template <typename T, typename Allocator>
struct ForwardList<T, Allocator>::Node final
{
    T value;
    Node* next{};

    template <typename... Args>
    Node(Args&&... args) : value{std::forward<Args>(args)...}
    {
    }
};

template <typename T, typename Allocator>
template <typename ValueType>
class ForwardList<T, Allocator>::Iterator
{
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = ValueType*;
    using reference = ValueType&;

    Iterator() = default;
    Iterator(Node* node) : current{node} {}

    reference operator*() const noexcept { return current->value; }
    pointer operator->() const noexcept { return &current->value; }

    Iterator& operator++() noexcept
    {
        current = current->next;
        return *this;
    }

    Iterator operator++(int) noexcept
    {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const Iterator& other) const noexcept
    {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const noexcept
    {
        return current != other.current;
    }

   private:
    Node* current{};
};

template <typename T, typename Allocator>
ForwardList<T, Allocator>::ForwardList() noexcept : head(nullptr), alloc()
{
    LOG("Default constructor");
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>::ForwardList(const Allocator& alloc) noexcept
    : head(nullptr), alloc(alloc)
{
    LOG("Constructor with allocator");
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>::ForwardList(const ForwardList& other)
    : head(nullptr), alloc(other.alloc)
{
    for (const auto& item : other)
    {
        push_front(item);
    }

    reverse();
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>::ForwardList(ForwardList&& other) noexcept
    : head(other.head), alloc(std::move(other.alloc))
{
    other.head = nullptr;
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>::~ForwardList()
{
    LOG("Destructor, cleaning ", std::distance(begin(), end()), " elements");

    clear();
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>& ForwardList<T, Allocator>::operator=(
    const ForwardList& other)
{
    if (this != &other)
    {
        clear();

        for (const auto& item : other)
        {
            push_front(item);
        }

        reverse();
    }

    return *this;
}

template <typename T, typename Allocator>
ForwardList<T, Allocator>& ForwardList<T, Allocator>::operator=(
    ForwardList&& other) noexcept
{
    if (this != &other)
    {
        clear();
        head = other.head;
        alloc = std::move(other.alloc);
        other.head = nullptr;
    }
    return *this;
}

template <typename T, typename Allocator>
bool ForwardList<T, Allocator>::empty() const noexcept
{
    return head == nullptr;
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::clear() noexcept
{
    while (head)
    {
        pop_front();
    }
}

template <typename T, typename Allocator>
template <typename... Args>
void ForwardList<T, Allocator>::emplace_front(Args&&... args)
{
    Node* new_node{};
    try
    {
        new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
        LOG("Allocated node at ", new_node);
        std::allocator_traits<NodeAllocator>::construct(
            alloc, new_node, std::forward<Args>(args)...);
        LOG("Constructed element at ", new_node);
    }
    catch (...)
    {
        LOG("Deallocated node at ", new_node);
        std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
        throw;
    }

    new_node->next = head;
    head = new_node;
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::push_front(const T& value)
{
    emplace_front(value);
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::push_front(T&& value)
{
    emplace_front(std::move(value));
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::pop_front()
{
    if (!head)
        return;

    Node* to_delete = head;
    head = head->next;

    LOG("Destroying element at ", to_delete);
    std::allocator_traits<NodeAllocator>::destroy(alloc, to_delete);
    LOG("Deallocated node at ", to_delete);
    std::allocator_traits<NodeAllocator>::deallocate(alloc, to_delete, 1);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::iterator
ForwardList<T, Allocator>::insert_after(iterator pos, const T& value)
{
    Node* new_node{};
    try
    {
        new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
        LOG("Allocated node at ", new_node);
        std::allocator_traits<NodeAllocator>::construct(alloc, new_node, value);
        LOG("Constructed element at ", new_node);
    }
    catch (...)
    {
        LOG("Deallocated node at ", new_node);
        std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
        throw;
    }

    new_node->next = pos.current->next;
    pos.current->next = new_node;
    return iterator(new_node);
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::reverse()
{
    if (head)
    {
        Node* prev = nullptr;
        Node* current = head;
        while (current)
        {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::iterator
ForwardList<T, Allocator>::begin() noexcept
{
    return iterator(head);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::iterator
ForwardList<T, Allocator>::end() noexcept
{
    return iterator(nullptr);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::const_iterator
ForwardList<T, Allocator>::begin() const noexcept
{
    return const_iterator(head);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::const_iterator
ForwardList<T, Allocator>::end() const noexcept
{
    return const_iterator(nullptr);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::const_iterator
ForwardList<T, Allocator>::cbegin() const noexcept
{
    return const_iterator(head);
}

template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::const_iterator
ForwardList<T, Allocator>::cend() const noexcept
{
    return const_iterator(nullptr);
}

}  // namespace containers