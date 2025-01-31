#ifndef FUNCTIONS
#define FUNCTIONS

#include<tuple>
#include<chrono>
#include<functional>

namespace sdfuncs {

    template <typename T, typename... Args>
    double timeit(T&& func, Args&&... args) {
        auto t1 = std::chrono::high_resolution_clock::now();
        int l = 100000; // number of iterations
        for (int i = 0; i < l; i++) {std::invoke(std::forward<T>(func), std::forward<Args>(args)...);}
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::micro>(t2 - t1).count();
        return duration/l;
    }

    double absoluteValue(double x);
    bool approx_equal(double a, double b, double acc, double eps) ;
}   
#endif // FUNCTIONS