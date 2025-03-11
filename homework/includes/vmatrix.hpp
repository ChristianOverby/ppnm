#ifndef vmatrix_HF
#define vmatrix_HF

#include <iostream>
#include <cassert>
#include <sstream>
#include "matrix.hpp" // Include your custom vector class

namespace ppnm {

    template <typename T>
    class vmatrix {
        public:
        pp::vector data;
        size_t rows, cols;
        // Default constructor
        vmatrix() : data(), rows(0), cols(0) {}

        // Constructor with dimensions
        vmatrix(size_t rows, size_t cols) : data(rows * cols), rows(rows), cols(cols) {
            for (size_t i = 0; i < rows * cols; i++) data[i] = T();
        }

        // Copy Constructor
        vmatrix(const vmatrix<T>& other) : data(other.data), rows(other.rows), cols(other.cols) {}

        // Move Constructor
        vmatrix(vmatrix<T>&& other) noexcept : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
            other.rows = 0;
            other.cols = 0;
        }

        // Copy Assignment
        vmatrix<T>& operator=(const vmatrix<T>& other) {
            if (this != &other) {
                data = other.data;  // `vector<T>` handles its own copying
                rows = other.rows;
                cols = other.cols;
            }
            return *this;
        }

        // Move Assignment
        vmatrix<T>& operator=(vmatrix<T>&& other) noexcept {
            if (this != &other) {
                data = std::move(other.data);  // Move vector<T> data
                rows = other.rows;
                cols = other.cols;
                other.rows = 0;
                other.cols = 0;
            }
            return *this;
        }

        // Destructor is now managed by vector<T>, so no need to delete[] manually
        ~vmatrix() = default;

        // Set value at (row, col)
        void set(size_t row, size_t col, const T& value) {
            if (row >= rows || col >= cols) {
                throw std::out_of_range("vmatrix indices out of range");
            }
            data[row * cols + col] = value;
        }

        // vmatrix addition
        vmatrix<T> operator+(const vmatrix<T>& other) const {
            assert(rows == other.rows && cols == other.cols);
            vmatrix<T> temp(rows, cols);
            for (size_t i = 0; i < rows * cols; i++) {
                temp.data[i] = data[i] + other.data[i];
            }
            return temp;
        }

        // vmatrix subtraction
        vmatrix<T> operator-(const vmatrix<T>& other) const {
            assert(rows == other.rows && cols == other.cols);
            vmatrix<T> temp(rows, cols);
            for (size_t i = 0; i < rows * cols; i++) {
                temp.data[i] = data[i] - other.data[i];
            }
            return temp;
        }

        // vmatrix multiplication (Scalar)
        vmatrix<T> operator*(const T& x) const {
            vmatrix<T> temp(rows, cols);
            for (size_t i = 0; i < rows * cols; i++) {
                temp.data[i] = data[i] * x;
            }
            return temp;
        }

        // vmatrix division (Scalar)
        vmatrix<T> operator/(const T& x) const {
            assert(x != T() && "Division by default constructed value. e.g. zero");
            vmatrix<T> temp(rows, cols);
            for (size_t i = 0; i < rows * cols; i++) {
                temp.data[i] = data[i] / x;
            }
            return temp;
        }

        // Overload the () operator for element access
        T& operator()(size_t row, size_t col) {
            if (row >= rows || col >= cols) {
                throw std::out_of_range("vmatrix indices out of range");
            }
            return data[row * cols + col];
        }

        // Const version for read-only access
        const T& operator()(size_t row, size_t col) const {
            if (row >= rows || col >= cols) {
                throw std::out_of_range("vmatrix indices out of range");
            }
            return data[row * cols + col];
        }

        // Friend function to overload the << operator
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const vmatrix<U>& obj);
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vmatrix<T>& obj) {
        std::ostringstream buffer;
        for (size_t i = 0; i < obj.rows; i++) {
            for (size_t j = 0; j < obj.cols; j++) {
                buffer << obj.data[i * obj.cols + j];
                if (j < obj.cols - 1) buffer << " ";
            }
            buffer << '\n';
        }
        return os << buffer.str();
    }

} // namespace ppnm

#endif // vmatrix_HF
