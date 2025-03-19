#ifndef __ODEINT_H__
#define __ODEINT_H__

#include <functional>
#include <vector>
#include <utility>
#include "../includes/matrix.hpp"

namespace pp {

    // values from https://en.wikipedia.org/wiki/List_of_Runge%E2%80%93Kutta_methods
    std::pair<pp::vector, pp::vector> stepper5(
        const std::function<pp::vector(double, const pp::vector&)>& f,
        const double x,                                   // the current value of the variable
        const pp::vector& y,                               // the current value y(x) of the sought function
        const double h                                    // the step to be taken
    );

    std::pair<pp::vector, pp::vector> stepper4(
        const std::function<pp::vector(double, const pp::vector&)>& f,
        const double x,                                   // the current value of the variable
        const pp::vector& y,                               // the current value y(x) of the sought function
        const double h                                    // the step to be taken
    );

    std::pair<pp::vector, std::vector<pp::vector>> driver(
        const std::function<pp::vector(double, const pp::vector&)>& f,
        double a,                                   // start value
        double b,                                   // end value
        pp::vector ystart,
        double h = 0.125,                           // intital stepsize
        double atol = 0.01,                          // absolute accuracy
        double rtol = 0.01,                           // relative accuracy
        int nmax = 10000                                   // Maximum number of steps
    );

    std::function<pp::vector(double)> make_ode_ivp_interpolant(
        const std::function<pp::vector(double, const pp::vector&)>& f,
        double a,                                   // start value
        double b,                                   // end value
        pp::vector ystart,
        double h = 0.125,                           // intital stepsize
        double atol = 0.01,                          // absolute accuracy
        double rtol = 0.01,                           // relative accuracy
        int nmax = 10000                                   // Maximum number of steps
    );

}




#endif // __ODEINT_H__