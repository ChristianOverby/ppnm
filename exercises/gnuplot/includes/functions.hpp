#ifndef FUNCTIONS
#define FUNCTIONS

#include <complex>

// Gamma function implemntation
namespace sfuns {
    double fgamma(double x);
    double lngamma(double x);
    double erf(double x);
    std::complex<double> G(std::complex<double> z);
}

#endif  // FUNCTIONS