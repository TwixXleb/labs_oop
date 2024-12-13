#pragma once
#include <memory_resource>
#include <stdexcept>
#include <utility>
#include "DynamicArrayIterator.h"

template <typename T>
class PmrDynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using value_type = T;
    using size_type = std::size_t;
    using iterator = DynamicArrayIterator<T>;
    using const_iterator = DynamicArrayIterator<const T>;

    PmrDynamicArray(std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    PmrDynamicArray(const PmrDynamicArray& other);
    PmrDynamicArray(PmrDynamicArray&& other) noexcept;
    PmrDynamicArray& operator=(const PmrDynamicArray& other);
    PmrDynamicArray& operator=(PmrDynamicArray&& other) noexcept;
    ~PmrDynamicArray();

    void push_back(const T& value);
    void push_back(T&& value);

    template <class... Args>
    T& emplace_back(Args&&... args);

    void pop_back();

    T& operator[](size_type index);
    const T& operator[](size_type index) const;

    size_type size() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    void reserve(size_type new_cap);
    void clear() noexcept;

private:
    void ensure_capacity(size_type min_cap);
    void reallocate(size_type new_cap);
    void deallocate_storage();

    allocator_type alloc_;
    T* data_;
    size_type size_;
    size_type capacity_;
};

#include "../src/lab_05/PmrDynamicArray.cpp"
