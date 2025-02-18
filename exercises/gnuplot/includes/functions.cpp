#include <cmath>
#include "functions.hpp"

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
    double erf(double x){
    /// single precision error function (Abramowitz and Stegun, from Wikipedia)
    if (x<0)
        return -erf(-x);
    const double a[5] = {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
    double t = 1/(1+0.3275911*x);
    double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));/* the right thing */
    return 1-sum*std::exp(-x*x);
    } 
        // Lanczos coefficients and parameter (from Wikipedia - https://en.wikipedia.org/wiki/Lanczos_approximation)
    const double lanczosCoeffs[] = {
        0.99999999999980993,
        676.5203681218851,
    -1259.1392167224028,
        771.32342877765313,
    -176.61502916214059,
        12.507343278686905,
    -0.1385710331296526,
        9.9843695780195716e-6,
        1.5056327351493116e-7
    };
    const int numCoeffs = 9;
    const double g = 7.0;  // Lanczos parameter

    // Gamma function for complex arguments using the Lanczos approximation
    std::complex<double> G(std::complex<double> z) {
        // Reflection formula: Gamma(z) * Gamma(1-z) = PI/sin(PI*z)
        if (z.real() < 0.5) {
            return M_PI / (std::sin(M_PI * z) * G(1.0 - z));
        } else {
            z -= 1.0;
            std::complex<double> x = lanczosCoeffs[0];
            for (int i = 1; i < numCoeffs; i++) {
                x += lanczosCoeffs[i] / (z + double(i));
            }
            std::complex<double> t = z + g + 0.5;
            return std::sqrt(2 * M_PI) * std::pow(t, z + 0.5) * std::exp(-t) * x;
        }
    }

}
