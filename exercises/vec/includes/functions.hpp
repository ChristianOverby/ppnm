#ifndef FUNCTIONS
#define FUNCTIONS

#include<tuple>
#include<chrono>
#include<cmath>
#include<functional>

namespace udfuncs {

     // should probably return more info. e.g. min, max, mean, median, std dev, etc.
    template <typename T, typename... Args>
    double timeit(T&& func, Args&&... args) {
        auto t1 = std::chrono::high_resolution_clock::now();
        int l = 100000; // number of iterations
        // std::invoke due to me wanting this to be any kind of function e.g. function pointer, lambda, functor.
        // std:::forward due to me wanting to preserve the rvalue/lvalue references
        for (int i = 0; i < l; i++) {std::invoke(std::forward<T>(func), std::forward<Args>(args)...);}
        auto t2 = std::chrono::high_resolution_clock::now();
        // in microseconds due to small function execution times
        auto duration = std::chrono::duration<double, std::micro>(t2 - t1).count();
        return duration/l;
    }

    template <typename T>
    bool approx_equal(T a, T b, T acc = static_cast<T>(1e-9), T eps = static_cast<T>(1e-9)) {
        if(std::abs(a-b) <= acc) {return true;}
        if(std::abs(a-b)/std::max(a,b) <= std::abs(eps)) {return true;}
        return false;
    }
}
#endif // FUNCTIONS