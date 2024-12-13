#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <memory_resource>
#include <stdexcept>
#include <utility>
#include <iterator>

template <typename T>
class DynamicArray {
private:
    std::pmr::polymorphic_allocator<T> allocator;
    T* data;
    std::size_t capacity;
    std::size_t size;

    void reallocate(std::size_t new_capacity);
    void destroy_elements();

public:
    explicit DynamicArray(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
    ~DynamicArray();

    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    void push_back(const T& value);
    void push_back(T&& value);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t get_size() const;
    std::size_t get_capacity() const;

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        pointer ptr;

        Iterator(pointer ptr) : ptr(ptr) {}
        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    };

    Iterator begin();
    Iterator end();
};

#include "../src/lab_05/dynamic_array.tpp"
#endif // DYNAMIC_ARRAY_H
