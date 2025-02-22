#ifndef FUNCTIONS_HF
#define FUNCTIONS_HF

#include <cmath>
#include <type_traits>
#include <limits>

// approximatively equal values to use when any floats are involved.
namespace ppnm {
template<typename T>
bool approx(const T& lval, const T& rval)
    {
        if constexpr (std::is_floating_point_v<T>) 
        {
            if (std::abs(lval - rval) <= std::numeric_limits<T>::epsilon()) {
                return true;  // Absolute error check - values close to 0
            }
            // relative precision check, useful for larger numbers, 
            return std::abs(lval - rval) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(lval), std::abs(rval));
        } else {
            return (lval == rval);  // Exact comparison for non-floating-point types
        }
    }
}; // typename ppnm

#endif // FUNCTIONS_HF