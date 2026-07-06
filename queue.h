#ifndef QUEUE_H
#define QUEUE_H

namespace mstd {
    template <typename T>
    class queue {
    private:
        T *data;
        size_t _capacity, _size;
        size_t head, tail;
        
        void resize() {
            T* new_array = new T[_capacity * 2];

            for (size_t i = 0; i < _size; i++) {
                size_t old_i = (head + i) % _capacity;
                new_array[i] = data[old_i];
            }

            delete[] data;
            data = new_array;
            _capacity *= 2;

            head = 0;
            tail = _size;
        }
        
    public:
        queue() : _size(0), _capacity(1), head(0), tail(0) {
            data = new T[_capacity];
        }
        
        queue(const queue& other) {
            _size = other._size;
            _capacity = other._capacity;
            head = other.head;
            tail = other.tail;
            data = new T[_capacity];
            for (size_t i = 0; i < _capacity; i++) {
                data[i] = other.data[i];
            }
        }

        queue(queue&& other) noexcept {
            _size = other._size;
            _capacity = other._capacity;
            head = other.head;
            tail = other.tail;
            data = other.data;

            other._size = 0;
            other._capacity = 0;
            other.data = nullptr;
        }
        
        ~queue() {
            delete[] data;
        }
        
        queue& operator=(queue&& other) noexcept {
            if (this == &other) return *this;

            delete[] data;

            _size = other._size;
            _capacity = other._capacity;
            head = other.head;
            tail = other.tail;
            data = other.data;

            other._size = 0;
            other._capacity = 0;
            other.data = nullptr;

            return *this;
        }

        queue& operator=(const queue& other) {
            if (this == &other) return *this;
            
            delete[] data;

            _size = other._size;
            _capacity = other._capacity;
            head = other.head;
            tail = other.tail;
            data = new T[_capacity];
            for(size_t i = 0; i < _capacity; i++) {
                data[i] = other.data[i];
            }

            return *this;
        }

        void push(const T& value) {
            if (_size == _capacity) resize();

            data[tail] = value;
            tail = (tail + 1) % _capacity;
            _size++;
        }

        void pop() { 
            if (!_size) return;

            head = (head + 1) % _capacity;
            _size--;
        }

        const T& front() { return data[head]; }
        const T& back() { return data[tail]; }
        bool isEmpty() { return !_size;}
        size_t size() const { return _size; }
    };
}

#endif
