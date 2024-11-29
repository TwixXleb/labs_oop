#include "../../include/dynamic_array.h"

template <typename T>
DynamicArray<T>::DynamicArray(allocator_type alloc)
        : alloc(alloc), data(nullptr), size_(0), capacity_(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
        : alloc(other.alloc), size_(other.size_), capacity_(other.capacity_) {
    data = alloc.allocate(capacity_);
    for (size_type i = 0; i < size_; ++i) {
        alloc.construct(&data[i], other.data[i]);
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
        : alloc(std::move(other.alloc)), data(other.data), size_(other.size_), capacity_(other.capacity_) {
    other.data = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        for (size_type i = 0; i < size_; ++i) {
            alloc.destroy(&data[i]);
        }
        alloc.deallocate(data, capacity_);
        alloc = other.alloc;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data = alloc.allocate(capacity_);
        for (size_type i = 0; i < size_; ++i) {
            alloc.construct(&data[i], other.data[i]);
        }
    }
    return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        for (size_type i = 0; i < size_; ++i) {
            alloc.destroy(&data[i]);
        }
        alloc.deallocate(data, capacity_);
        alloc = std::move(other.alloc);
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    for (size_type i = 0; i < size_; ++i) {
        alloc.destroy(&data[i]);
    }
    alloc.deallocate(data, capacity_);
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = alloc.allocate(capacity_);
        for (size_type i = 0; i < size_; ++i) {
            alloc.construct(&new_data[i], data[i]);
        }
        for (size_type i = 0; i < size_; ++i) {
            alloc.destroy(&data[i]);
        }
        alloc.deallocate(data, capacity_);
        data = new_data;
    }
    alloc.construct(&data[size_], value);
    ++size_;
}

template <typename T>
typename DynamicArray<T>::reference DynamicArray<T>::operator[](size_type index) {
    return data[index];
}

template <typename T>
typename DynamicArray<T>::const_reference DynamicArray<T>::operator[](size_type index) const {
    return data[index];
}

template <typename T>
typename DynamicArray<T>::size_type DynamicArray<T>::size() const {
    return size_;
}

template <typename T>
typename DynamicArray<T>::size_type DynamicArray<T>::capacity() const {
    return capacity_;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::begin() {
    return iterator(data);
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::end() {
    return iterator(data + size_);
}

template <typename T>
DynamicArray<T>::iterator::iterator(pointer ptr) : ptr_(ptr) {}

template <typename T>
typename DynamicArray<T>::iterator::reference DynamicArray<T>::iterator::operator*() const {
    return *ptr_;
}

template <typename T>
typename DynamicArray<T>::iterator::pointer DynamicArray<T>::iterator::operator->() const {
    return ptr_;
}

template <typename T>
typename DynamicArray<T>::iterator& DynamicArray<T>::iterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++ptr_;
    return temp;
}