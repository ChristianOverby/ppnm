#include <cmath>
#include "functions.h"

// Gamma function implemntation
namespace sfuns {
    double fgamma(double x) {
        if (x < 0) {return M_PI/std::sin(M_PI*x)/fgamma(1-x);}
        if (x < 9) {return fgamma(x+1)/x;}
        double lnfgamma = x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*M_PI/x)/2;
        return std::exp(lnfgamma);
    }
    double lngamma(double x) {
        if (x <= 0) {return std::nan("");}
        if (x < 9) {return lngamma(x+1) - log(x);}
        double lngamma = x * std::log(x + 1/(12*x - 1/(x*10))) - x + std::log(2*M_PI/x)/2;
        return lngamma;
    }
}
