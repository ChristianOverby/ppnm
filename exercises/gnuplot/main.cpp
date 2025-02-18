#include "includes/functions.hpp"
#include <complex>
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    // errorfunction
    for (double x = -3; x <= 3; x+=1.0/16){
        std::cout << x << " " << sfuns::erf(x) << std::endl;
    }
    // Gamma
    std::cout << std::endl << std::endl;
    double dx=1.0/256;
	for(double x = -5+dx/2; x <= 5; x += dx){
        std::cout << x << " " << sfuns::fgamma(x) << std::endl;
    }
    // ln(Gamma)
    std::cout << std::endl << std::endl;
    for(double x = dx; x <= 10; x += dx){
        std::cout << x << " " << sfuns::lngamma(x) << std::endl;
    }
    std::cout << std::endl << std::endl;
    // factorial loop
    double f=1;
    std::cout << 1 << " " << f << std::endl; // Output for i = 1
	for(int i=1;i<=10;i++){
		f *= i;
		std::cout << (i+1) << " " << f << std::endl;
	}

    // Define the grid in the complex plane.
    double x_min = -5.0, x_max = 5.0;
    double y_min = -5.0, y_max = 5.0;
    const int nx = 300; // number of grid points in real direction
    const int ny = 300; // number of grid points in imaginary direction

    // Generate grid and compute |Gamma(z)| for each point.
    for (int i = 0; i < nx; i++) {
        double x = x_min + (x_max - x_min) * i / (nx - 1);
        for (int j = 0; j < ny; j++) {
            double y = y_min + (y_max - y_min) * j / (ny - 1);
            std::complex<double> z(x, y);
            std::complex<double> gamma_val = sfuns::G(z);
            double abs_gamma = std::abs(gamma_val);
            double phase = std::atan2(gamma_val.imag(), gamma_val.real());
            // double arg_gamma = std::arg(gamma_val);  // Compute the argument (phase) of Gamma(z)
            // Write: real-part, imaginary-part, |Gamma(z)|, arg(Gamma(z))
            std::cout << x << " " << y << " " << abs_gamma << " " << phase << std::endl;
        }
        std::cout << "\n"; // blank line to separate grid rows (helps pm3d in gnuplot)
    }
}
