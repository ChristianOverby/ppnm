#ifndef GENLIST_HF
#define GENLIST_HF

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "functions.hpp"

namespace ppnm
{

    template<typename T>
    class vector 
    { 
            public:
            T* data = nullptr;
            size_t size = 0;
            size_t capacity = 0;    
            // Default constructor
            vector() : data(nullptr), size(0), capacity(0) {}
            // other constructors
            vector(size_t startCap, bool init = true) : data(new T[startCap]), size(startCap), capacity(startCap) {
                // Fill data with 0's
                if(init) {
                for (size_t i = 0; i < size; i++) {
                    data[i] = T();
                }
                }
            }


            // destructor
            ~vector()
            {
                // Just delete whatever spot on the heap the data points to
                size = 0;
                capacity = 0;
                delete[] data;
            }
            // Copy constructor
            vector(const vector<T>& other) 
            {
                // Allocate memory for the new vector
                size = other.size;
                capacity = other.capacity;
                data = new T[capacity];

                // Copy elements
                for (size_t i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
            // Move constructor - Found this noexcept keyword that is useful for omptimization apparently
            // Only to be used with functions that cannot possibly throw exceptions, e.g. the move constructor.
            // simply moves data
            vector(vector<T>&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) 
            {
                // reset the moved vector
                other.data = nullptr;
                other.size = 0;
                other.capacity = 0;
            }
            // copy assginment
            vector<T>& operator=(const vector<T>& other) 
            {
                if (this != &other) {
                    delete[] data;  // Free existing memory

                    size = other.size;
                    capacity = other.capacity;
                    data = new T[capacity];  // Allocate new memory
                    for (size_t i = 0; i < size; i++) {
                        data[i] = other.data[i];  // Copy elements
                    }
                }
                return *this;
            }
            // Move assignment operator
            vector<T>& operator=(vector<T>&& other) noexcept 
            {
                if (this != &other) {
                    // Free the current resources
                    delete[] data;

                    // Steal the resources from 'other'
                    data = other.data;
                    size = other.size;
                    capacity = other.capacity;

                    // Reset 'other' to an empty state
                    other.data = nullptr;
                    other.size = 0;
                    other.capacity = 0;
                }
                return *this;
            }

        private:
            // allocate memory when needed
            void reAllocateMemory(const size_t newCap) 
            {
                // Should allocate more memory, copy or maybe move old memory to new block and delete old memory if not moved.
                T* newDataBlock = new T[newCap];

                if (newCap < size)
                    size = newCap;
                
                for (size_t i = 0; i < size; i++)
                    newDataBlock[i] = std::move(data[i]);

                delete[] data;
                data = newDataBlock;
                capacity = newCap;
            };

        public:
            // add some element to the end of list
            void add(const T& value)
            {
                if (size == capacity) {
                    reAllocateMemory(capacity == 0 ? 1 : capacity * 2);
                }
                
                data[size] = value;
                size++;
            }
            // remove the i'th element of the vector
            void remove(size_t i) 
            {
                if (i >= size || i < 0) {
                    std::cerr << "Index out of bounds: " << i << std::endl;
                    return;
                }
                // Shift elements to the left to fill the gap
                for (size_t j = i; j < size - 1; ++j) {
                    data[j] = std::move(data[j + 1]);
                }

                // Destroy the last element
                data[size - 1].~T();

                // Decrease the size
                size--;
            }
            // reset vector
            void clear()
            {
                for (size_t i = 0; i < size; i++)
                    data[i].~T();

                size = 0;
            }
            // dot product
            T dot(const vector<T>& v) const 
            {
                if (size != v.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size");
                }
                T sum = 0;
                for (size_t i = 0; i<size; i++)
                {
                    sum += data[i]*v.data[i];
                }
            return sum;
            };
            // The same as the norm
            T magnitude() const 
            {
                T sum = 0;
                for (size_t i = 0; i < size; ++i) {
                    sum += data[i] * data[i];
                }
                return std::sqrt(sum);
            }

            // returns the data stored at some index
            T& operator[](size_t index) {
                return data[index];
            }
            // returns the data stored at some index read only
            const T& operator[](size_t index) const {
                return data[index];
            }

            vector<T>& operator+=(const vector<T>& other) { // addition assignment
            if (size != other.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size at addition");
                }
                for (size_t i=0; i<size; i++) data[i] += other.data[i];
                return *this;
            }

            vector<T>& operator-=(const vector<T>& other) { // subtraction assignment
            if (size != other.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size at addition");
                }
                for (size_t i=0; i<size; i++) data[i] -= other.data[i];
                return *this;
            }

            vector<T>& operator-() { // unary negation
                for (size_t i=0; i<size; i++) data[i] = -data[i];
                return *this;
            }

            vector<T>& operator*=(const vector<T>& other) { // dot product assignment
                if (size != other.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size at addition");
                }
                for (size_t i=0; i<size; i++) data[i] *= other.data[i];
                return *this;
            }

            vector<T>& operator*=(T x) { // scalar multiplication assignment
                for (size_t i=0; i<size; i++) data[i] *= x;
                return *this;
            }
            vector<T>& operator/=(T x) { // scalar division assignment
                for (size_t i=0; i<size; i++) data[i] /= x;
                return *this;
            }

            // Overloads the plus operator
            vector<T> operator+(const vector<T>& other) const
            {
                if (size != other.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size at addition");
                }

                // Initialize the result vector with the correct size
                vector<T> result(size, false);  // Allocate memory upfront
                for (size_t i = 0; i < size; i++)
                {
                    result.data[i] = data[i] + other[i];  // Directly assign to the elements
                }
                return result;
            }

            // Overloads the minus operator
            vector<T> operator-(const vector<T>& other) const
            {
                if (size != other.size) 
                {
                    throw std::invalid_argument("Vectors must be of the same size at subtraction");
                }

                // Initialize the result vector with the correct size
                vector<T> result(size, false);  // Allocate memory upfront
                for (size_t i = 0; i < size; i++)
                {
                    result.data[i] = data[i] - other[i];  // Directly assign to the elements
                }
                return result;
            }

            // Overloads the multiplication operator
            vector<T> operator*(const T& scalar) const
            {
                vector<T> result(size, false);  // Allocate memory upfront
                for (size_t i = 0; i < size; i++)
                {
                    result.data[i] = data[i] * scalar;  // Directly assign to the elements
                }
                return result;
            }

            // Overloads the division operator
            vector<T> operator/(const T& scalar) const
            {
                if (approx(scalar, T())) 
                {
                    throw std::invalid_argument("Division by 0 in vector division");
                }

                vector<T> result(size, false);  // Allocate memory upfront
                for (size_t i = 0; i < size; i++)
                {
                    result.data[i] = data[i] / scalar;  // Directly assign to the elements
                }
                return result;
            }

            bool operator==(const vector& vec) const {
                if(vec.size != size) {
                    return false;
                }
                for (size_t i =0; i < size; i++) {
                    if(!ppnm::approx(data[i], vec[i])) return false;
                }
                return true;
            }

            // prints vector, kinda redudant probably will be removed
            void printVector() const
            {
                for (size_t i = 0; i < size; i++)
                    std::cout << data[i] << " ";
                std::cout << std::endl;
            }
            // iterator implementation
            T* begin(){ return data;} // first element
            T* end() {return data + size; } // element + one past

            // const versions for read access
            const T* begin() const { return data;} // first element
            const T* end() const {return data + size; } // one past last element per convention.

            // friend function to overload the << operator
            template<typename U>
            friend std::ostream& operator<<(std::ostream& os, const vector<U>& obj);

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const vector<T>& obj) {
        for(size_t i = 0; i<obj.size; i++){
            os << obj.data[i] << " ";
        }
        return os;
    }


};
#endif // GENLIST_HF

