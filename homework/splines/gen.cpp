#include <cmath>
#include <iostream>
#include <fstream>
#include "../includes/matrix.hpp"
#include "spline.hpp"

namespace pp
{
    void genLsplineData()
    {
        int n = 10;

        pp::vector x(n);
        pp::vector y(n);
        for (int i = 0; i<n; i++) {
            x[i] = i;
            y[i] = std::cos(i);
        }

        pp::lspline lspline(x, y);

        std::ofstream file("lspline.csv");
        if(!file.is_open()) { std::cerr << "could not open lspline.csv" << std::endl;}
        file << "x, f(x), F(x)\n";
        for (double x_i = 0; x_i < n - 1; x_i += 0.5) {
            file << x_i << ", " << lspline.linterp(x_i) << ", " << lspline.linterpInteg(x_i) << "\n";
        }
        file.close();

        double z = M_PI;
        std::cout << "Integral of cos(x) from x = 0 to z = " << z << ": " << lspline.linterpInteg(z) << std::endl;
    }
    
    void genQsplineData()
    {
        int n = 10;

        pp::vector x(n);
        pp::vector y(n);
        for (int i = 0; i<n; i++) {
            x[i] = i;
            y[i] = std::cos(i);
        }

        pp::qspline qspline(x, y);
        std::ofstream file("qspline.csv");
        if(!file.is_open()) { std::cerr << "could not open qspline.csv" << std::endl;}
        file << "x, f(x), F(x), df(x)/dx\n";
        for (double x_i = 0; x_i < n - 1; x_i += 0.2) {
            file << x_i << ", " << qspline.qinterp(x_i) << ", " << qspline.qinterpInteg(x_i) << ", " << qspline.qinterpDerivative(x_i) << "\n";
        }
        file.close();

        double z = M_PI;
        std::cout << "Integral of cos(x) from x = 0 to z = " << z << ": " << qspline.qinterpInteg(z) << std::endl;
    }
    
    void genCsplineData()
    {
        int n = 10;

        pp::vector x(n);
        pp::vector y(n);
        for (int i = 0; i<n; i++) {
            x[i] = i;
            y[i] = std::cos(i);
        }
        std::cout << x << "\n" << y << std::endl;
        pp::cspline cspline(x, y);
        std::ofstream file("cspline.csv");
        if(!file.is_open()) { std::cerr << "could not open cspline.csv" << std::endl;}
        file << "x, f(x), F(x), df(x)/dx\n";
        for (double x_i = 0; x_i < n - 1; x_i += 0.1) {
            file << x_i << ", " << cspline.cinterp(x_i) << ", " << cspline.cinterpInteg(x_i) << ", " << cspline.cinterpDerivative(x_i) << "\n";
        }
        file.close();

        double z = M_PI;
        std::cout << "Integral of cos(x) from x = 0 to z = " << z << ": " << cspline.cinterpInteg(z) << std::endl;
    }
}