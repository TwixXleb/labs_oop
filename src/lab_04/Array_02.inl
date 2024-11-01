// Array_02.inl
#pragma once

template<class T>
void Array_02<T>::increase_capacity() {
    size_t new_capacity = capacity * 2;
    std::shared_ptr<T[]> new_data(new T[new_capacity], std::default_delete<T[]>());

    // Move elements
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }

    data = std::move(new_data);
    capacity = new_capacity;
}

template<class T>
Array_02<T>::Array_02() : capacity(1), size(0), data(new T[capacity], std::default_delete<T[]>()) {}

template<class T>
Array_02<T>::Array_02(const Array_02& other)
    : capacity(other.capacity), size(other.size), data(new T[other.capacity], std::default_delete<T[]>()) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template<class T>
Array_02<T>::Array_02(Array_02&& other) noexcept
    : capacity(other.capacity), size(other.size), data(std::move(other.data)) {
    other.capacity = 0;
    other.size = 0;
}

template<class T>
Array_02<T>& Array_02<T>::operator=(const Array_02& other) {
    if (this == &other)
        return *this;
    capacity = other.capacity;
    size = other.size;
    data.reset(new T[capacity], std::default_delete<T[]>());
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

template<class T>
Array_02<T>& Array_02<T>::operator=(Array_02&& other) noexcept {
    if (this == &other)
        return *this;
    capacity = other.capacity;
    size = other.size;
    data = std::move(other.data);
    other.capacity = 0;
    other.size = 0;
    return *this;
}

template<class T>
void Array_02<T>::push_back(const T& element) {
    if (size >= capacity) {
        increase_capacity();
    }
    data[size++] = element;
}

template<class T>
void Array_02<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    for (size_t i = index + 1; i < size; ++i) {
        data[i - 1] = std::move(data[i]);
    }
    --size;
}

template<class T>
T& Array_02<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template<class T>
const T& Array_02<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template<class T>
size_t Array_02<T>::get_size() const {
    return size;
}
