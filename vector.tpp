#pragma once

#include "Vector.h"
#include <algorithm>
#include <utility>

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(std::size_t size, const T& value)
    : data_(new T[size]), size_(size), capacity_(size) {
    std::fill(data_, data_ + size, value);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : Vector(init.size()) {
    std::copy(init.begin(), init.end(), data_);
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
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
T& Vector<T>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T>
T& Vector<T>::at(std::size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) expandCapacity();
    data_[size_++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) --size_;
}

template <typename T>
void Vector<T>::clear() {
    size_ = 0;
}

template <typename T>
std::size_t Vector<T>::size() const {
    return size_;
}

template <typename T>
std::size_t Vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Vector<T>::reserve(std::size_t newCapacity) {
    if (newCapacity > capacity_) {
        T* newData = new T[newCapacity];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
}

template <typename T>
void Vector<T>::resize(std::size_t newSize, const T& value) {
    if (newSize > capacity_) reserve(newSize);
    if (newSize > size_) {
        std::fill(data_ + size_, data_ + newSize, value);
    }
    size_ = newSize;
}

template <typename T>
void Vector<T>::expandCapacity() {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
}

template <typename T>
T* Vector<T>::begin() {
    return data_;
}

template <typename T>
T* Vector<T>::end() {
    return data_ + size_;
}

template <typename T>
const T* Vector<T>::begin() const {
    return data_;
}

template <typename T>
const T* Vector<T>::end() const {
    return data_ + size_;
}
