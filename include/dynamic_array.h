
#ifndef LAB0_DYNAMIC_ARRAY_H
#define LAB0_DYNAMIC_ARRAY_H

#include <memory>
#include "memory_resourse.h"


template <typename T>
class DynamicArray {
private:
    allocator_type alloc;
    pointer data;
    size_type size_;
    size_type capacity_;

public:
    using value_type = T;
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    DynamicArray(allocator_type alloc = allocator_type());
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;
    ~DynamicArray();

    void push_back(const T& value);
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    size_type size() const;
    size_type capacity() const;

    iterator begin();
    iterator end();
};

template <typename T>
class DynamicArray<T>::iterator {
private:
    pointer ptr_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator(pointer ptr);
    reference operator*() const;
    pointer operator->() const;
    iterator& operator++();
    iterator operator++(int);
    friend bool operator==(const iterator& a, const iterator& b) {
        return a.ptr_ == b.ptr_;
    }
    friend bool operator!=(const iterator& a, const iterator& b) {
        return a.ptr_ != b.ptr_;
    }
};

#endif //LAB0_DYNAMIC_ARRAY_H
