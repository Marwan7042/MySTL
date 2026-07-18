#ifndef MVECTOR_H
#define MVECTOR_H

#include <iostream>
#include <stdexcept>

namespace mstd {
    template <typename T>
    class vector {
    private:
        T* data;
        typedef T *iterator;
        size_t _capacity;
        size_t _size;

        void resize() {
            T* arr = new T[_capacity * 2];
            for (size_t i = 0; i < _size; i++) {
                arr[i] = data[i];
            }
            
            delete[] data;
            data = arr;
            _capacity *= 2;
        }

    public:
        iterator begin() { return data; }
        iterator end() { return data + _size; }
        
        vector() : _size(0), _capacity(1) {
            data = new T[_capacity];
        }

        vector(size_t s) : _size(s), _capacity(s) {
            data = new T[_capacity];
        }

        vector(size_t s, const T& default_value) : _size(s), _capacity(s) {
            data = new T[_capacity];
            for (size_t i = 0; i < _size; i++)
                data[i] = default_value;
        }

        vector(const vector& other) {
            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for (size_t i = 0; i < _size; i++) {
                data[i] = other.data[i];
            }
        }

        vector(vector&& other) noexcept {
            _size = other._size;
            _capacity = other._capacity;
            data = other.data;

            other._size = 0;
            other._capacity = 0;
            other.data = nullptr;
        }

        ~vector() {
            delete[] data;
        }

        vector& operator=(vector&& other) noexcept {
            if (this == &other) return *this;

            delete[] data;

            _size = other._size;
            _capacity = other._capacity;
            data = other.data;

            other._size = 0;
            other._capacity = 0;
            other.data = nullptr;

            return *this;
        }

        vector& operator=(const vector& other) {
            if (this == &other) return *this;
            
            delete[] data;

            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for(size_t i = 0; i < _size; i++) {
                data[i] = other.data[i];
            }

            return *this;
        }

        void push_back(const T& value) {
            if (_size == _capacity) resize();
            data[_size++] = value;
        }

        void pop_back() {
            if (_size) _size--;
        }

        void insert(size_t index, const T& value) {
            if (index > _size) throw std::out_of_range("Index out of range.");
            if (_size == _capacity) resize();

            for (size_t i = _size; i > index; i--) {
                data[i] = data[i - 1];
            }

            data[index] = value;
            _size++;
        }

        void remove(size_t index) {
            if (index >= _size) throw std::out_of_range("Index out of range.");
            
            for (size_t i = index; i < _size - 1; i++) {
                data[i] = data[i + 1];
            }

            _size--;
        }

        void reverse() {
            size_t start = 0;
            size_t end = _size - 1;

            while (start < end) {
                T tmp = data[start]; 
                data[start] = data[end];
                data[end] = tmp;
                start++; end--;
            }
        }

        T& operator[](size_t index) {
            if (index >= _size) throw std::out_of_range("Index out of range.");
            return data[index];
        }
        
        const T& operator[](size_t index) const {
            if (index >= _size) throw std::out_of_range("Index out of range.");
            return data[index];
        }

        bool operator==(const vector& other) const {
            if (_size != other.size()) return false;
            for (size_t i = 0; i < _size; i++){
                if (data[i] == other.data[i]) continue;
                return false;
            }
            return true;
        }
        
        size_t capacity() const { return _capacity; }
        size_t size() const { return _size; }
        void clear() { _size = 0; }
        bool isEmpty() const { return !_size; } 
        T& front() { return data[0]; }
        T& back() { return data[_size - 1]; }
    };
}

#endif
