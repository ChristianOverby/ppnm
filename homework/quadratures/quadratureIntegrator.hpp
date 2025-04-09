#ifndef __QUADRATUREINTEGRATOR_H__
#define __QUADRATUREINTEGRATOR_H__

#include <cmath>
#include <functional>
#include <tuple>

namespace pp {

    std::tuple<double, double, int> integrate(const std::function<double(double)>& f, const double a, const double b, const double δ=1e-4, const double ε=1e-4,
                    double f2 = NAN, double f3 = NAN, int evals = 0);
    
    std::tuple<double, double, int> CCintegrate(const std::function<double(double)>& f, const double a, const double b, const double δ=1e-4, const double ε=1e-4);

    std::tuple<double, double, int> integrate_inf(const std::function<double(double)>& f, const double a, const double b, const double δ=1e-4, const double ε=1e-4);

}


#endif // __QUADRATUREINTEGRATOR_H__