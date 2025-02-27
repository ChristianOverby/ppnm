#ifndef MATRIX_HF
#define MATRIX_HF

#include "vector.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "functions.hpp"

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
                for(size_t i = 0; i<rows*cols; i++) {data[i] = T();}
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
            // destructor
            ~matrix()
            {
                delete[] data;
            }   
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
                assert(vector.getSize() == rows && "Size of vector is not the same as rows in matrix");
                for(size_t i = 0; i < rows; i++)    
                    {
                        data[i*cols + c] = vector[i];
                    }
            }
            // get a coloumn as a vector, this method was also added due to the ease of GM ortho with vectors
            ppnm::vector<T> getCol(size_t c)
            {
                ppnm::vector<T> temp;
                for(size_t i = 0; i < rows; i++)
                    {
                        temp.add(data[i*cols + c]);
                    }
                return temp;
            }

            // getter methods for rows and cols
            size_t getRows() const {
                return rows;
            }
            size_t getCols() const {
                return cols;
            }


            // not sure if i need this method yet. Implement later if needed
            void resize(const size_t& newcols, const size_t& newrows){
                if(newrows == rows && newcols == cols) return;
                std::cerr << "Function resize(const size_t& newcols, const size_t& newrows) not implemented" << std::endl;
                std::abort();  // Aborts the program
            }
        // Creation methods
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
            // Return a transposed matrix
            matrix<T> transpose() const 
            {
                matrix<T> tmpTransposed(cols, rows);

                for(size_t i = 0; i < rows; i++){
                    for(size_t j = 0; j < cols; j++) {
                        tmpTransposed.data[j*rows +i] = data[i* cols + j];
                    }
                }    
                return tmpTransposed;
            }
            // Return randomized matrix of same size
            matrix<T> randomizedMatrix(const int& start,const int& end ) const 
            {
                if (start >= end) {
                    throw std::invalid_argument("start must be less than end");
                }
            matrix<T> tmpMatrix(rows, cols);
            for (size_t i = 0; i < tmpMatrix.getRows(); ++i) {
                for (size_t j = 0; j < tmpMatrix.getCols(); ++j) {
                    tmpMatrix.set(i, j, static_cast<T>((std::rand()) % (end-start)) + start);

                }
            }
            return tmpMatrix;
            }


            bool lowerTriangular() const 
            {
                for (size_t i = 0; i < std::min(rows, cols); i++) {
                    for (size_t j = i + 1; j < cols; j++) {  // Only check above the diagonal (i, j)
                        if (!ppnm::approx(data[i * cols + j], T())) {
                            return false;  // Found a nonzero element above the diagonal
                        }
                    }
                }
                return true;
            }

            bool upperTriangular() const 
            {
                for (size_t i = 1; i < rows; i++) {  // Start from row 1, since this makes sense.
                    for (size_t j = 0; j < std::min(i, cols); j++) {  // Only check below the diagonal (i, j)
                        if (!ppnm::approx(data[i * cols + j], T())) {
                            std::cout << "\n Nonzero below diagonal at (" << i << ", " << j 
                          << "): " << data[i * cols + j] << std::endl;
                            return false;  // Found a nonzero element below the diagonal
                        }
                    }
                }
                return true;
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
            // matrix subtraction overload
            matrix<T> operator-(const matrix<T>& other) const
            {
                assert(rows == other.rows && cols == other.cols); // Ensure sizes match
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i] - other.data[i]; }
                return temp;
            }
            // matrix multiplication overload (Scalar)
            matrix<T> operator*(const T& x) const
            {
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i]*x; }
                return temp;
            }
            // Matrix multiplication overload (vector)
            ppnm::vector<T> operator*(const ppnm::vector<T>& vec) const 
            {
                assert(cols == vec.getSize() && "rows in matrix and size of vector should be the same.");
                ppnm::vector<T> tempVec;
                for(size_t i = 0; i < rows; i++) 
                {
                    T sum = 0;
                    for(size_t j = 0; j < cols; j++)
                    {
                        sum += data[j+i*cols]*vec[j];
                    }
                    tempVec.add(sum);
                }
                return tempVec;
            }

            // Matrix multiplication overload (vector)
            ppnm::matrix<T> operator*(const ppnm::matrix<T>& other) const 
            {
                assert(cols == other.getRows() && "rows in matrix and size of vector should be the same.");
                ppnm::matrix<T> tempMat(rows, other.getCols());
                for (size_t i = 0; i < rows; i++) 
                {
                    for (size_t j = 0; j < other.getCols(); j++) 
                    {
                        T sum = 0;
                        for (size_t k = 0; k < cols; k++) // Iterate over shared dimension
                        {
                            sum += data[k + i * cols] * other(k, j); 
                        }
                        tempMat(i, j) = sum; // Assign result
                    }
                }
                return tempMat;
            }

            // Matrix divison overload (scalar)
            matrix<T> operator/(const T& x) const
            {
                assert(x != T() && "Division by default constructed value. e.g. zero");
                matrix<T> temp(rows, cols);
                for(size_t i = 0; i < rows * cols ; i++) {temp.data[i] = data[i]*x; }
                return temp;
            }

            bool operator==(const matrix<T>& mat) const
            {
                if (mat.getRows() != rows || mat.getCols() != cols)
                    return false;
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    if (!ppnm::approx(mat(i, j), data[i * cols + j])) {
                        return false;
                    }
                }
            }
            return true;
            }
            
            // Overload the () operator for element access and modification
            T& operator()(size_t row, size_t col) 
            {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                return data[row * cols + col];
            }

            // Const version of () operator overlaod for read-only access
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