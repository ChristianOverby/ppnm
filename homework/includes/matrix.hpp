#ifndef MATRIX_HF
#define MATRIX_HF

#include "vector.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include <type_traits>
#include <limits>

namespace ppnm {

    template <typename T>
    class matrix{
        private:
            T* data;
            size_t rows, cols;
        public:
            // default constructor
            matrix() : data(nullptr), rows(0), cols(0){}
            // constructor
            matrix(size_t rows, size_t cols) : data(new T[rows*cols]), rows(rows), cols(cols){
                for(size_t i = 0; i<rows*cols; i++) data[i] = T();
            }
            // copy constructor
            matrix(matrix<T> const& other) : data(new T[other.rows*other.cols]),rows(other.rows), cols(other.cols){
                for(size_t i = 0; i<rows*cols; i++) data[i] = other.data[i];
            }
            // move constructor
            matrix(matrix<T>&& other) : data(other.data), rows(other.rows), cols(other.cols)
            {
                other.data = nullptr;
                other.rows = 0;
                other.cols = 0;
            }
            // delete constructor
            ~matrix(){delete[] data;}   
            // copy assignment
            matrix<T>& operator=(matrix<T> const& other)
            {
                if(this != &other){
                    delete[] data;
                    data = new T[rows*cols];
                    rows = other.rows;
                    cols = other.cols;
                    for(size_t i = 0; i<rows*cols; i++) data[i] = other.data[i];
                }
                return *this;
            }

            // Move assignment
            matrix<T>& operator=(matrix<T>&& other) 
            {
                if(this != &other) {
                    delete[] data;
                    data = other.data;
                    rows = other.rows;
                    cols = other.cols;
                    other.data = nullptr;
                    other.rows = 0;
                    other.cols = 0;
                }
                return *this; // Returning a reference to the current object
            }

    // Methods
            // Method to set the value at a specific row and column
            void set(size_t row, size_t col, const T& value) {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                data[row * cols + col] = value;
            }

            // setter method for diagonal
            void setDiagonal(const T& value, int offset = 0)
            {
                for (size_t i = 0; i < rows*cols; i++)
                    {
                        if(i+offset >= 0 && i+offset < cols)
                            data[i * cols + i + offset] = value;
                    }
            }

            // set a coloumn as a vector, this method was added due to the ease of GM ortho with vectors
            void setCol(size_t c, ppnm::vector<T> vector) 
            {
                assert(vector.getSize() == rows && "Size");
                for(size_t i = 0; i < rows; i++)
                    {
                        data[i*cols + c] = vector[i];
                    }
            }

            // not sure if i need this method yet. Implement later if needed
            void resize(const size_t& newcols, const size_t& newrows){
                if(newrows == rows && newcols == cols) return;
                std::cerr << "Function resize(const size_t& newcols, const size_t& newrows) not implemented" << std::endl;
                std::abort();  // Aborts the program
            }

            // method for creating an idenitity matrix of same size as another matrix
            matrix<T> identity() const 
            {
                assert(rows == cols && "Identity matrix must be square");

                matrix<T> tmpIdentity(cols, rows);

                for (size_t i = 0; i < rows * cols; ++i) {
                    tmpIdentity.data[i] = 0;
                }

                for(size_t i = 0; i< rows; i++) {
                    tmpIdentity.data[i * cols + i] = 1;
                }
                return tmpIdentity;
            }

            matrix<T> transpose() const 
            {
                matrix<T> tmpTransposed(rows, cols);

                for(size_t i = 0; i < rows; i++){
                    for(size_t j = 0; j < cols; j++) {
                        tmpTransposed.data[j*rows +i] = data[i* cols + j];
                    }
                }    
                return tmpTransposed;
            }

            bool approx(const T& lval, const T& rval) const
            {
                if constexpr (std::is_floating_point_v<T>) 
                {
                    return std::abs(lval - rval) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(lval), std::abs(rval));
                }
                else return (lval == rval);
            }


            
            bool lowerTriangular() const 
            {
                for (size_t i = 0; i < rows; i++) {
                    for (size_t j = i + 1; j < cols; j++) {  // Only check above the diagonal (i, j)
                        if (!approx(data[i * cols + j], 0)) {
                            return false;  // Found a nonzero element above the diagonal
                        }
                    }
                }
                return true;
            }

            bool upperTriangular() const 
            {
                for (size_t i = 1; i < rows; i++) {  // Start from row 1
                    for (size_t j = 0; j < i; j++) {  // Only check below the diagonal (i, j)
                        if (!approx(data[i * cols + j], 0)) {
                            return false;  // Found a nonzero element below the diagonal
                        }
                    }
                }
                return true;  // If all off-diagonal elements are approximately zero, it's upper triangular
            }


    // Operator overloads
            // Matrix addition
            matrix<T> operator+(const matrix<T>& other) const
            {
                assert(rows == other.rows && cols == other.cols); // Ensure sizes match
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i] + other.data[i]; }
                return temp;
            }
            // matrix subtraction
            matrix<T> operator-(const matrix<T>& other) const
            {
                assert(rows == other.rows && cols == other.cols); // Ensure sizes match
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i] - other.data[i]; }
                return temp;
            }
            // matrix multiplication (Scalar)
            matrix<T> operator*(const T& x) const
            {
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i]*x; }
                return temp;
            }
            // Matrix divison (scalar)
            matrix<T> operator/(const T& x) const
            {
                assert(x != T() && "Division by default constructed value. e.g. zero");
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i]*x; }
                return temp;
            }

            // Overload the () operator for element access and modification
            T& operator()(size_t row, size_t col) 
            {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                return data[row * cols + col];
            }

            // Const version for read-only access
            const T& operator()(size_t row, size_t col) const 
            {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                return data[row * cols + col];
            }

            // iterator implementation
            const T* begin() const { return data; } // first element
            const T* end() const { return data + rows*cols; } // one past last element per convention.


            // friend function to overload the << operator
            template<typename U>
            friend std::ostream& operator<<(std::ostream& os, const matrix<U>& obj);

    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const matrix<T>& obj) {
        // buffer implemented in memory so i dont have to do expensive I/O calls all the time.
        std::ostringstream buffer;
        for(size_t i = 0; i<obj.rows; i++){
            for(size_t j = 0; j<obj.cols; j++){
                buffer << obj.data[i*obj.cols + j];
                if (j < obj.cols - 1) buffer << " ";
            }
            buffer << '\n';
        }

        return os << buffer.str();
    }

}




#endif // MATRIX_HF