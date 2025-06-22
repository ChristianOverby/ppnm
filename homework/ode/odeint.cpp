#include "odeint.hpp"
#include "../splines/spline.hpp"
#include <cmath>
#include <utility>

namespace pp
{
    std::pair<pp::vector, pp::vector> stepper5(
            const std::function<pp::vector(double, const pp::vector&)>& f, // Function dy/xy = f(x, y)
            double x,                                               // Current x
            const vector& y,                                        // Current y(x)
            double h                                                // Step size
            )
    {
        // Butcher tableau coefficients
        const double c2 = 1.0 / 4.0;
        const double c3 = 3.0 / 8.0;
        const double c4 = 12.0 / 13.0;
        const double c5 = 1.0;
        const double c6 = 1.0 / 2.0;

        const double a21 = 1.0 / 4.0;
        const double a31 = 3.0 / 32.0;
        const double a32 = 9.0 / 32.0;

        const double a41 = 1932.0 / 2197.0;
        const double a42 = -7200.0 / 2197.0;
        const double a43 = 7296.0 / 2197.0;

        const double a51 = 439.0 / 216.0;
        const double a52 = -8.0;
        const double a53 = 3680.0 / 513.0;
        const double a54 = -845.0 / 4104.0;

        const double a61 = -8.0 / 27.0;
        const double a62 = 2.0;
        const double a63 = -3544.0 / 2565.0;
        const double a64 = 1859.0 / 4104.0;
        const double a65 = -11.0 / 40.0;

        const double b1_5 = 16.0 / 135.0;
        const double b3_5 = 6656.0 / 12825.0;
        const double b4_5 = 28561.0 / 56430.0;
        const double b5_5 = -9.0 / 50.0;
        const double b6_5 = 2.0 / 55.0;

        const double b1_4 = 25.0 / 216.0;
        const double b3_4 = 1408.0 / 2565.0;
        const double b4_4 = 2197.0 / 4104.0;
        const double b5_4 = -1.0 / 5.0;

        // Compute stages
        pp::vector k0 = f(x, y); // k0 is f(x, y)
        pp::vector k1 = f(x + c2 * h, y + h*(a21 * k0));
        pp::vector k2 = f(x + c3 * h, y + h*(a31 * k0 + a32 * k1));
        pp::vector k3 = f(x + c4 * h, y + h*(a41 * k0 + a42 * k1 + a43 * k2));
        pp::vector k4 = f(x + c5 * h, y + h*(a51 * k0 + a52 * k1 + a53 * k2 + a54 * k3));
        pp::vector k5 = f(x + c6 * h, y + h*(a61 * k0 + a62 * k1 + a63 * k2 + a64 * k3 + a65 * k4));

        pp::vector yh_5 = y + h*(b1_5*k0 + b3_5*k2 + b4_5*k3 + b5_5*k4 + b6_5*k5);
        pp::vector yh_4 = y + h*(b1_4*k0 + b3_4*k2 + b4_4*k3 + b5_4*k4);
        pp::vector dy = yh_5-yh_4;
        
        std::pair<pp::vector, pp::vector> bar(yh_5, dy);
        return {yh_4, dy}; 
    }

    std::pair<pp::vector, std::vector<pp::vector>> driver(
            const std::function<pp::vector(double, const pp::vector&)>& f,
            double a,                                   // start value
            double b,                                   // end value
            pp::vector ystart,
            double h,                                   // intital stepsize
            double atol,                                 // absolute accuracy
            double rtol,                                 // relative accuracy
            int nmax                                    // Maximum number of steps
            )
    {
        double x = a;
        pp::vector y = ystart;
        pp::vector xlist; xlist.push_back(x);
        std::vector<pp::vector> ylist; ylist.push_back(y);
        int step = 0;
        // double hmax = 0.1;
        // double hmin = 1e-6;
        while(x < b && step < nmax){
            if(x>=b) {std::pair<pp::vector, std::vector<pp::vector>> bar(xlist,ylist);return bar;} /* job done */
            if(x+h>b) h=b-x;               /* last step should end at b */
            std::pair<pp::vector, pp::vector> yhdy = stepper5(f,x,y,h);
            //double tol = (atol+rtol*yhdy.first.norm()) * std::sqrt(h/(b-a));
            double tol = atol + rtol * yhdy.first.norm();  // Replaced with stanrad tolerance calculations.
            double err = yhdy.second.norm();
            if(err<=tol){ // accept step
            x+=h; y=yhdy.first;
            xlist.push_back(x);
            ylist.push_back(y);
            }
            h *= std::min(std::pow(tol/err,0.25)*0.95 , 2.0); // readjust stepsize
            // h = std::min(h, hmax);  // Enforce maximum step size
            // h = std::max(h, hmin);  // Enforce minimum step size
            step++;
            }

        return {xlist, ylist};
    }//driver

    std::function<pp::vector(double)> make_ode_ivp_interpolant(
        const std::function<pp::vector(double, const pp::vector&)>& f,
        double a,                                   // start value
        double b,                                   // end value
        pp::vector ystart,
        double h,                           // intital stepsize
        double atol,                          // absolute accuracy
        double rtol,                           // relative accuracy
        int nmax                                   // Maximum number of steps
    )
    {
        auto [xlist, ylist] = driver(f, a, b, ystart, h, atol, rtol, nmax);
        std::vector<pp::cspline> splines;
        int n = xlist.size();
        int m = ylist[0].size();
        
        splines.reserve(m);
        for(int i = 0; i<m; i++) {
            pp::vector vec(n);
            for (int j = 0; j < n; ++j) {
                vec[j] = ylist[j][i];  // Extract i-th component for all
            }
            pp::cspline tempspline(xlist, vec);
            splines.push_back(tempspline);
        }

        std::function<vector(double)> interp = [splines, m](double x) -> vector {
            vector res(m);
            for (int i = 0; i < m; ++i) {
                res[i] = splines[i].cinterp(x);
            }
            return res;
        };

        return interp;
    }

}