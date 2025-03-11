#ifndef FUNCTIONS_HF
#define FUNCTIONS_HF

#include <cmath>
#include <type_traits>
#include <chrono>
#include<functional>
// approximatively equal values to use when any floats are involved.
namespace pp {
template<typename T>
bool approx(const T& lval, const T& rval, T tol = 1e-8)
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

 // should probably return more info. e.g. min, max, mean, median, std dev, etc.
    template <typename T, typename... Args>
    double timeit(T&& func, Args&&... args) {
        auto t1 = std::chrono::high_resolution_clock::now();
        int l = 1; // number of iterations
        // std::invoke due to me wanting this to be any kind of function e.g. function pointer, lambda, functor.
        // std:::forward due to me wanting to preserve the rvalue/lvalue references
        for (int i = 0; i < l; i++) {std::invoke(std::forward<T>(func), std::forward<Args>(args)...);}
        auto t2 = std::chrono::high_resolution_clock::now();
        // in microseconds due to small function execution times
        auto duration = std::chrono::duration<double, std::micro>(t2 - t1).count();
        return duration/l;
    }
}; // typename ppnm

#endif // FUNCTIONS_HF