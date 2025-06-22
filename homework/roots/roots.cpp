#include "roots.hpp"
#include <iostream>
#include "../includes/matrix.hpp"

namespace pp
{
    pp::matrix jacobian(std::function<pp::vector(const pp::vector&)> f, pp::vector x, pp::vector fx, pp::vector dx)
    {
    if (dx.size() == 0 || dx.norm() == 0) {
        dx = pp::vector(x.size());
        for (int i = 0; i < x.size(); ++i) {
            dx[i] = std::max(1e-8, std::abs(x[i]) * std::pow(2, -26));
        }
    }
    if (fx.size() == 0) fx = f(x);

    pp::matrix J = pp::matrix(x.size(), x.size());
    for (int j = 0; j < x.size(); ++j) {
        double old = x[j];
        x[j] += dx[j];
        pp::vector df = f(x) - fx;
        for (int i = 0; i < x.size(); ++i) {
            J[i, j] = df[i] / dx[j];
        }
        x[j] = old; // Restore
    }
    return J;
    }    

    pp::vector newton(std::function<pp::vector(const pp::vector&)> f, pp::vector start, double acc, pp::vector δx)
    {
    pp::vector x=start;
    const int max_iter = 100000;
    int iter = 0;
    // Initialize δx with safe defaults per component
    if (δx.size() == 0) {
        δx = pp::vector(x.size());
        for (int i = 0; i < x.size(); ++i) {
            δx[i] = std::max(1e-8, std::abs(x[i]) * std::pow(2, -26));
        }
    }
    // pp::vector dx = 
    pp::vector fx = f(x), Dx(x.size()), z,fz;
    while(fx.norm() >= acc && iter++ < max_iter){ /* Newton's iterations */
        matrix J=jacobian(f,x,fx,δx);
        pp::QRGS QRdecomposition(J);
        Dx = QRdecomposition.solve(-fx); /* Newton's step */

        if (Dx.norm() < std::pow(2, -26) * x.norm()) {
            std::cerr << "Step size too small, aborting procedure." << std::endl;
            break;
        }
        double λ = 1.0;
        z = x + λ * Dx;
        fz = f(z);
        while(fz.norm() > (1 - λ / 2) * fx.norm()){ /* linesearch */
            if (λ < 1.0 / 2048.0) {
                //std::cerr << "λ too small line search might have failed.\n";
                break;
            }
            λ /= 2.0;
            z = x + λ * Dx;
            fz = f(z);
        }
        x = z;
        fx = fz;
    }

    if (std::isnan(x.norm()) || std::isinf(x.norm())) {
        std::cerr << "Invalid numerical values" << std::endl;
    }
    
    if (iter >= max_iter) {
        std::cerr << "Warning: Newton method did not converge within " << max_iter << " iterations.\n";
    }
    return x;
    }
}