#ifndef GENLIST_HF
#define GENLIST_HF

#include <iostream>

namespace userdef 
{

    template<typename T>
    class GenList 
    {
        private: 
            T* data = nullptr;
            size_t size = 0;
            size_t capacity = 0;    

        public:
            GenList() 
            {
                // Always allocates 2 elements. This is easier for me to implement due to the way i've defined the add funciton.
                reAllocateMemory(2); 
            }

            ~GenList()
            {
                // Just delete whatever spot on the heap the data points to
                delete[] data;
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
                if (size >= capacity)
                    reAllocateMemory(capacity + capacity/2);
                
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
            void printGenList() const
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


    };


};
#endif // GENLIST_HF

