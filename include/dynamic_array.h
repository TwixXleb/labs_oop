#ifndef LAB0_DYNAMIC_ARRAY_H
#define LAB0_DYNAMIC_ARRAY_H

#pragma once
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <memory_resource>

template<typename T>
class DynamicArrayIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    DynamicArrayIterator(pointer ptr) : current_(ptr) {}

    reference operator*() const { return *current_; }
    pointer operator->() { return current_; }

    DynamicArrayIterator& operator++() {
        ++current_;
        return *this;
    }

    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.current_ == b.current_;
    }

    friend bool operator!=(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.current_ != b.current_;
    }

private:
    pointer current_;
};

template<typename T>
class DynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using iterator = DynamicArrayIterator<T>;
    using const_iterator = DynamicArrayIterator<const T>;

    DynamicArray(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
            : alloc_(mr), data_(nullptr), size_(0), capacity_(0)
    {}

    ~DynamicArray() {
        clear();
        if (data_) {
            alloc_.deallocate(data_, capacity_);
            data_ = nullptr;
        }
        size_ = 0;
        capacity_ = 0;
    }

    void push_back(const T& value) {
        ensure_capacity(size_ + 1);
        alloc_.construct(data_ + size_, value);
        ++size_;
    }

    void push_back(T&& value) {
        ensure_capacity(size_ + 1);
        alloc_.construct(data_ + size_, std::move(value));
        ++size_;
    }

    reference operator[](size_type idx) {
        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[idx];
    }

    const_reference operator[](size_type idx) const {
        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[idx];
    }

    size_type size() const noexcept {
        return size_;
    }

    iterator begin() noexcept {
        return iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }

    const_iterator end() const noexcept {
        return const_iterator(data_ + size_);
    }

    void clear() {
        for (size_type i = 0; i < size_; ++i) {
            alloc_.destroy(data_ + i);
        }
        size_ = 0;
    }

private:
    void ensure_capacity(size_type new_cap) {
        if (new_cap <= capacity_) {
            return;
        }
        size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        while (new_capacity < new_cap) {
            new_capacity *= 2;
        }
        T* new_data = alloc_.allocate(new_capacity);
        for (size_type i = 0; i < size_; ++i) {
            alloc_.construct(new_data + i, std::move(data_[i]));
            alloc_.destroy(data_ + i);
        }
        if (data_) {
            alloc_.deallocate(data_, capacity_);
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }

    allocator_type alloc_;
    T* data_;
    size_type size_;
    size_type capacity_;
};


#endif