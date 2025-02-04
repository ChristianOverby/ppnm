#include"functions.hpp"

namespace sdfuncs {
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


    bool approx_equal(double a, double b, double acc, double eps) {
        if(absoluteValue(a-b) <= acc) {return true;}
        if(absoluteValue(a-b)/maximum(a,b) <= absoluteValue(eps)) {return true;}
        return false;
    }
}