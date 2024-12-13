#include <dynamic_array.h>

template <typename T>
void DynamicArray<T>::reallocate(std::size_t new_capacity) {
    T* new_data = allocator.allocate(new_capacity);
    for (std::size_t i = 0; i < size; ++i) {
        new (new_data + i) T(std::move(data[i]));
        data[i].~T();
    }
    allocator.deallocate(data, capacity);
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
void DynamicArray<T>::destroy_elements() {
    for (std::size_t i = 0; i < size; ++i) {
        data[i].~T();
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource* resource)
        : allocator(resource), data(nullptr), capacity(0), size(0) {}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    destroy_elements();
    allocator.deallocate(data, capacity);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
        : allocator(other.allocator), data(nullptr), capacity(other.capacity), size(other.size) {
    data = allocator.allocate(capacity);
    for (std::size_t i = 0; i < size; ++i) {
        new (data + i) T(other.data[i]);
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        destroy_elements();
        allocator.deallocate(data, capacity);

        capacity = other.capacity;
        size = other.size;
        data = allocator.allocate(capacity);
        for (std::size_t i = 0; i < size; ++i) {
            new (data + i) T(other.data[i]);
        }
    }
    return *this;
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
        : allocator(std::move(other.allocator)), data(other.data), capacity(other.capacity), size(other.size) {
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        destroy_elements();
        allocator.deallocate(data, capacity);

        allocator = std::move(other.allocator);
        data = other.data;
        capacity = other.capacity;
        size = other.size;

        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size == capacity) {
        reallocate(capacity == 0 ? 1 : capacity * 2);
    }
    new (data + size) T(value);
    ++size;
}

template <typename T>
void DynamicArray<T>::push_back(T&& value) {
    if (size == capacity) {
        reallocate(capacity == 0 ? 1 : capacity * 2);
    }
    new (data + size) T(std::move(value));
    ++size;
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
std::size_t DynamicArray<T>::get_size() const {
    return size;
}

template <typename T>
std::size_t DynamicArray<T>::get_capacity() const {
    return capacity;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(data);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(data + size);
}
