#include"functions.hpp"

namespace udfuncs {
    // could be made into a template function
    double absoluteValue(double x) {
        unsigned long long i = reinterpret_cast<const unsigned long long&>(x);
        // clear the sign bit
        i &= 0x7FFFFFFFFFFFFFFF;
        return reinterpret_cast<const double&>(i);
    }
    constexpr double maximum(const double& a, const double& b) {
        return a > b ? a : b;
    }
}