#include<chrono>
#include<functional>
#include"functions.hpp"

namespace sdfuncs {
    double absoluteValue(double x) {
        unsigned long long i = reinterpret_cast<const unsigned long long&>(x);
        i &= 0x7FFFFFFFFFFFFFFF;
        return reinterpret_cast<const double&>(i);
    }
    constexpr double maximum(const double& a, const double& b) {
        return a > b ? a : b;
    }

    bool approx_equal(double a, double b, double acc, double eps) {
        if(std::abs(a-b) <= acc) {return true;}
        if(std::abs(a-b)/std::max(a,b) <= std::abs(eps)) {return true;}
        return false;
    }
}