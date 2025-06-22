#include "minimiser.hpp"
#include <cmath>
#include "../linear_equations/QRGS.hpp"

namespace pp
{
        pp::vector gradient(std::function<double(const pp::vector&)> f, const pp::vector x)
    {
        const double fx = f(x);  // Only once
        pp::vector gf(x.size());

        for(int i = 0; i < x.size(); ++i) {
            double dxi = (1 + std::abs(x[i])) * std::pow(2, -26);
            pp::vector xtemp = x;
            xtemp[i] += dxi;
            gf[i] = (f(xtemp) - fx) / dxi;
        }
        return gf;
    }

    pp::matrix hessian(std::function<double(const pp::vector&)> f, const pp::vector x)
    {
        const pp::vector gfx = gradient(f, x);  // Only once
        pp::matrix H(x.size(), x.size());

        for(int i = 0; i < x.size(); ++i) {
            double dxi = (1 + std::abs(x[i])) * std::pow(2, -13);
            pp::vector xtemp = x;
            xtemp[i] += dxi;

            pp::vector dgf = gradient(f, xtemp) - gfx;
            for(int j = 0; j < x.size(); ++j) {
                H[j, i] = dgf[j] / dxi;
            }
        }
        return H;
    }

    std::pair<pp::vector, double> newton(std::function<double(const pp::vector&)> f, pp::vector x, double acc)
    {
        const int max_iter = 100000;
        int iter = 0;
        double fx = f(x);           // Cache f(x)
        pp::vector g = gradient(f, x);  // Initial gradient

        while(iter < max_iter && g.norm() > acc) {
            pp::matrix H = hessian(f, x);
            pp::QRGS decomp(H);
            pp::vector dx = decomp.solve(-g);
            double λ = 1.0;

            double fx_new;
            while (λ >= 1.0 / 1024.0) {
                fx_new = f(x + λ * dx);
                if (fx_new < fx)
                    break;
                λ /= 2.0;
            }

            x = x + λ * dx;
            fx = fx_new;           // Update cached f(x)
            g = gradient(f, x);    // Update gradient
            ++iter;
        }

        return {x, iter};
    }

    



}