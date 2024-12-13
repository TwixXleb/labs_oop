#pragma once
#include <iterator>
#include <cstddef>

template <typename T>
class DynamicArrayIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using reference         = T&;
    using pointer           = T*;

    DynamicArrayIterator(pointer ptr) : ptr_(ptr) {}

    DynamicArrayIterator(const DynamicArrayIterator&) = default;
    DynamicArrayIterator(DynamicArrayIterator&&) noexcept = default;
    DynamicArrayIterator& operator=(const DynamicArrayIterator&) = default;
    DynamicArrayIterator& operator=(DynamicArrayIterator&&) noexcept = default;
    ~DynamicArrayIterator() = default;

    reference operator*() const { return *ptr_; }
    pointer   operator->() const { return ptr_; }

    DynamicArrayIterator& operator++() {
        ++ptr_;
        return *this;
    }

    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.ptr_ == b.ptr_;
    }

    friend bool operator!=(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.ptr_ != b.ptr_;
    }

private:
    pointer ptr_;
};
