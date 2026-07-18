#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdexcept>

namespace mstd{
    class Matrix {
    private:
        size_t rows, cols;
        mstd::vector<float> data;

    public:
        Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows * cols, 0.0f) {}

        float& operator()(size_t i, size_t j) { return data[(i * cols) + j]; }
        const float& operator()(size_t i, size_t j) const { return data[(i * cols) + j]; }
        
        Matrix T() const;    
        Matrix operator+(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;

        void print() const;
    };
}

#endif