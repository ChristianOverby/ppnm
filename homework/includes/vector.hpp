#ifndef GENLIST_HF
#define GENLIST_HF

#include <iostream>

namespace ppnm
{

    template<typename T>
    class vector 
    {
        private: 
            T* data = nullptr;
            size_t size = 0;
            size_t capacity = 0;    

        public:
            // Default constructor
            vector() : data(nullptr), size(0), capacity(0) {}
            // other constructors
            vector(size_t startCap) : data(new T[startCap]), size(0), capacity(startCap) {}


            // destructor
            ~vector()
            {
                // Just delete whatever spot on the heap the data points to
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
            void add(const T& value)
            {
                if (size == capacity) {
                    reAllocateMemory(capacity == 0 ? 1 : capacity * 2);
                }
                
                data[size] = value;
                size++;
            }
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
            void clear()
            {
                for (size_t i = 0; i < size; i++)
                    data[i].~T();

                size = 0;
            }
            T& operator[](size_t index) {
                return data[index];
            }

            const T& operator[](size_t index) const {
                return data[index];
            }
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

