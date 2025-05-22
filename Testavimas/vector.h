#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <limits>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

template <typename T>
class Vector {
private:
    T* vec_;
    size_t capacity_;
    size_t size_;
    size_t reallocations; // Skaitiklis perskirstymams

    void reallocate(size_t new_capacity) {
        T* new_vec = new T[new_capacity];
        try {
            std::move(vec_, vec_ + size_, new_vec);
        } catch (...) {
            delete[] new_vec;
            throw;
        }
        delete[] vec_;
        vec_ = new_vec;
        capacity_ = new_capacity;
    }

public:
    // Member types
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Constructors
    Vector() : vec_(nullptr), capacity_(0), size_(0) {}

    explicit Vector(size_type count) : vec_(new T[count]), capacity_(count), size_(count) {
        std::fill_n(vec_, size_, T());
    }

    Vector(size_type count, const T& value) : vec_(new T[count]), capacity_(count), size_(count) {
        std::fill_n(vec_, size_, value);
    }

    Vector(std::initializer_list<T> list) : vec_(new T[list.size()]), capacity_(list.size()), size_(list.size()) {
        std::copy(list.begin(), list.end(), vec_);
    }

    // Copy constructor
    Vector(const Vector& other) : vec_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
        std::copy(other.vec_, other.vec_ + size_, vec_);
    }

    // Move constructor
    Vector(Vector&& other) noexcept : 
        vec_(other.vec_), 
        capacity_(other.capacity_), 
        size_(other.size_) {
        other.vec_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Destructor
    ~Vector() {
        delete[] vec_;
    }

    // Assignment operators
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] vec_;
            vec_ = other.vec_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.vec_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Element access
    reference operator[](size_type pos) {
        return vec_[pos];
    }

    const_reference operator[](size_type pos) const {
        return vec_[pos];
    }

    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("out of range");
        }
        return vec_[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("out of range");
        }
        return vec_[pos];
    }

    reference front() {
        return vec_[0];
    }

    const_reference front() const {
        return vec_[0];
    }

    reference back() {
        return vec_[size_ - 1];
    }

    const_reference back() const {
        return vec_[size_ - 1];
    }

    T* data() noexcept {
        return vec_;
    }

    const T* data() const noexcept {
        return vec_;
    }

    // Iterators
    iterator begin() noexcept {
        return vec_;
    }

    const_iterator begin() const noexcept {
        return vec_;
    }

    const_iterator cbegin() const noexcept {
        return vec_;
    }

    iterator end() noexcept {
        return vec_ + size_;
    }

    const_iterator end() const noexcept {
        return vec_ + size_;
    }

    const_iterator cend() const noexcept {
        return vec_ + size_;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    // Capacity
    bool empty() const noexcept {
        return size_ == 0;
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    size_type getReallocations() const {
        return reallocations;
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    void reserve(size_type new_cap) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }

    // Modifiers
    void clear() noexcept {
        size_ = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return emplace(pos, std::move(value));
    }

    iterator erase(const_iterator pos) {
        if (pos < cbegin() || pos >= cend()) {
            throw std::out_of_range("out of range");
        }
        iterator non_const_pos = begin() + (pos - cbegin());
        std::move(non_const_pos + 1, end(), non_const_pos);
        --size_;
        return non_const_pos;
    }

    iterator erase(const_iterator first, const_iterator last) {
        if (first < cbegin() || last > cend() || first > last) {
            throw std::out_of_range("out of range");
        }
        iterator non_const_first = begin() + (first - cbegin());
        if (first != last) {
            iterator non_const_last = begin() + (last - cbegin());
            std::move(non_const_last, end(), non_const_first);
            size_ -= (last - first);
        }
        return non_const_first;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            reallocations++;
        }
        vec_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        vec_[size_++] = std::move(value);
    }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (&vec_[size_]) T(std::forward<Args>(args)...);
        return vec_[size_++];
    }

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        if (pos < cbegin() || pos > cend()) {
            throw std::out_of_range("Vector::emplace - iterator out of range");
        }
        size_type offset = pos - cbegin();
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        iterator insert_pos = begin() + offset;
        if (insert_pos != end()) {
            std::move_backward(insert_pos, end(), end() + 1);
        }
        new (&(*insert_pos)) T(std::forward<Args>(args)...);
        ++size_;
        return insert_pos;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void resize(size_type count) {
        if (count > capacity_) {
            reserve(count);
        }
        if (count > size_) {
            std::fill(vec_ + size_, vec_ + count, T());
        }
        size_ = count;
    }

    void resize(size_type count, const value_type& value) {
        if (count > capacity_) {
            reserve(count);
        }
        if (count > size_) {
            std::fill(vec_ + size_, vec_ + count, value);
        }
        size_ = count;
    }

    void swap(Vector& other) noexcept {
        std::swap(vec_, other.vec_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Comparison operators
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        return std::equal(begin(), end(), other.begin());
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }

    bool operator<=(const Vector& other) const {
        return !(*this > other);
    }

    bool operator>(const Vector& other) const {
        return other < *this;
    }

    bool operator>=(const Vector& other) const {
        return !(*this < other);
    }
};

// Non-member swap function
template <typename T>
void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}

#endif // VECTOR_H