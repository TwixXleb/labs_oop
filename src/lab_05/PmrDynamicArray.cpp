#include "../../include/PmrDynamicArray.h"
#include <utility>
#include <new>

template <typename T>
PmrDynamicArray<T>::PmrDynamicArray(std::pmr::memory_resource* mr)
        : alloc_(mr), data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
PmrDynamicArray<T>::PmrDynamicArray(const PmrDynamicArray& other)
        : alloc_(other.alloc_.resource()), data_(nullptr), size_(0), capacity_(0)
{
    reserve(other.size_);
    for (size_type i = 0; i < other.size_; ++i) {
        alloc_.construct(data_ + i, other.data_[i]);
    }
    size_ = other.size_;
}

template <typename T>
PmrDynamicArray<T>::PmrDynamicArray(PmrDynamicArray&& other) noexcept
        : alloc_(other.alloc_.resource()), data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
PmrDynamicArray<T>& PmrDynamicArray<T>::operator=(const PmrDynamicArray& other) {
    if (this != &other) {
        clear();
        if (capacity_ < other.size_) {
            deallocate_storage();
            reserve(other.size_);
        }
        for (size_type i = 0; i < other.size_; ++i) {
            alloc_.construct(data_ + i, other.data_[i]);
        }
        size_ = other.size_;
    }
    return *this;
}

template <typename T>
PmrDynamicArray<T>& PmrDynamicArray<T>::operator=(PmrDynamicArray&& other) noexcept {
    if (this != &other) {
        clear();
        deallocate_storage();

        alloc_ = typename PmrDynamicArray<T>::allocator_type(other.alloc_.resource());
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
PmrDynamicArray<T>::~PmrDynamicArray() {
    clear();
    deallocate_storage();
}

template <typename T>
void PmrDynamicArray<T>::push_back(const T& value) {
    ensure_capacity(size_ + 1);
    alloc_.construct(data_ + size_, value);
    ++size_;
}

template <typename T>
void PmrDynamicArray<T>::push_back(T&& value) {
    ensure_capacity(size_ + 1);
    alloc_.construct(data_ + size_, std::move(value));
    ++size_;
}

template <typename T>
template <class... Args>
T& PmrDynamicArray<T>::emplace_back(Args&&... args) {
    ensure_capacity(size_ + 1);
    alloc_.construct(data_ + size_, std::forward<Args>(args)...);
    ++size_;
    return data_[size_ - 1];
}

template <typename T>
void PmrDynamicArray<T>::pop_back() {
    if (size_ > 0) {
        alloc_.destroy(data_ + size_ - 1);
        --size_;
    }
}

template <typename T>
T& PmrDynamicArray<T>::operator[](size_type index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
const T& PmrDynamicArray<T>::operator[](size_type index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
typename PmrDynamicArray<T>::size_type PmrDynamicArray<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool PmrDynamicArray<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
typename PmrDynamicArray<T>::iterator PmrDynamicArray<T>::begin() noexcept {
    return iterator(data_);
}

template <typename T>
typename PmrDynamicArray<T>::iterator PmrDynamicArray<T>::end() noexcept {
    return iterator(data_ + size_);
}

template <typename T>
typename PmrDynamicArray<T>::const_iterator PmrDynamicArray<T>::begin() const noexcept {
    return const_iterator(data_);
}

template <typename T>
typename PmrDynamicArray<T>::const_iterator PmrDynamicArray<T>::end() const noexcept {
    return const_iterator(data_ + size_);
}

template <typename T>
typename PmrDynamicArray<T>::const_iterator PmrDynamicArray<T>::cbegin() const noexcept {
    return const_iterator(data_);
}

template <typename T>
typename PmrDynamicArray<T>::const_iterator PmrDynamicArray<T>::cend() const noexcept {
    return const_iterator(data_ + size_);
}

template <typename T>
void PmrDynamicArray<T>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        reallocate(new_cap);
    }
}

template <typename T>
void PmrDynamicArray<T>::clear() noexcept {
    for (size_type i = 0; i < size_; ++i) {
        alloc_.destroy(data_ + i);
    }
    size_ = 0;
}

template <typename T>
void PmrDynamicArray<T>::ensure_capacity(size_type min_cap) {
    if (capacity_ < min_cap) {
        size_type new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        if (new_cap < min_cap) {
            new_cap = min_cap;
        }
        reallocate(new_cap);
    }
}

template <typename T>
void PmrDynamicArray<T>::reallocate(size_type new_cap) {
    T* new_data = alloc_.allocate(new_cap);
    for (size_type i = 0; i < size_; ++i) {
        alloc_.construct(new_data + i, std::move_if_noexcept(data_[i]));
        alloc_.destroy(data_ + i);
    }
    alloc_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_cap;
}

template <typename T>
void PmrDynamicArray<T>::deallocate_storage() {
    if (data_) {
        alloc_.deallocate(data_, capacity_);
        data_ = nullptr;
        capacity_ = 0;
    }
}
