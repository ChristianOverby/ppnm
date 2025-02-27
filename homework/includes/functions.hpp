#ifndef FUNCTIONS_HF
#define FUNCTIONS_HF

#include <cmath>
#include <type_traits>

// approximatively equal values to use when any floats are involved.
namespace ppnm {
template<typename T>
bool approx(const T& lval, const T& rval, T tol = 1e-10)
{
    static_assert(std::is_arithmetic_v<T>, "Dude why are you comparing non arithmetic types?");

    if constexpr (std::is_floating_point_v<T>)  // constexpr is a nice flag that just tells compiler that this can be done at compiletime
    {
        T diff = std::abs(lval - rval);
        T largest = std::max(std::abs(lval), std::abs(rval));

        // Absolute check for very small numbers
        if (diff <= tol) {
            return true;
        }

        // Relative precision check for larger numbers
        return diff <= tol * largest;
    } 
    else 
    {
        return (lval == rval); // Exact match for non-floating types
    }
}
}; // typename ppnm

#endif // FUNCTIONS_HF