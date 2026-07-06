#include "matrix.h"
#include <iostream>
#include <stdexcept>

Matrix Matrix::T() const {
    Matrix transposed(this->cols, this->rows);
    for (size_t i = 0; i < this->rows; i++) for (size_t j = 0; j < this->cols; j++) transposed(j, i) = (*this)(i, j);
    return transposed;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) throw std::invalid_argument("Shape mismatch.");

    Matrix Mat(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++)
        Mat.data[i] = this->data[i] + other.data[i];

    return Mat;
}


Matrix Matrix::operator*(const Matrix& other) const {
    if (this->cols != other.rows) throw std::invalid_argument("Matrix A colomns must match matrix B rows.");

    Matrix result(this->rows, other.cols);
    Matrix t = other.T();

    for (size_t i = 0; i < this->rows; i++){
        for (size_t j = 0; j < other.cols; j++){
            float sum = 0.0f;
            for (size_t k = 0; k < this->cols; k++) 
                sum += (*this)(i, k) * t(j, k);
            result(i, j) = sum;
        }
    }
    return result;
}

void Matrix::print() const {
    for (size_t r = 0; r < this->rows; r++) {
        std::cout << "[ ";
        for (size_t c = 0; c < this->cols; c++) {
            std::cout << (*this)(r, c) << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}