#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void expandCapacity();

public:
    // Konstruktoriai
    Vector();
    Vector(std::size_t size, const T& value = T());
    Vector(std::initializer_list<T> init);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    // Operatoriai
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // Pagrindinės funkcijos
    void push_back(const T& value);
    void pop_back();
    void clear();
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
    void reserve(std::size_t newCapacity);
    void resize(std::size_t newSize, const T& value = T());
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    // Iteratoriai
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};

#include "Vector.tpp"
#endif