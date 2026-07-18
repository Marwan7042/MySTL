#ifndef STACK_H
#define STACK_H

#include "vector.h"

namespace mstd {
    template <typename T>
    class stack {
    private:
        mstd::vector<T> v;
        
    public:
        void push(const T& value) { v.push_back(value); }
        void pop() { v.pop_back(); }
        T& front() { return v.back(); }
        
        bool isEmpty() const { return v.isEmpty(); }
        size_t getSize() const { return v.size(); }
    };
}

#endif
