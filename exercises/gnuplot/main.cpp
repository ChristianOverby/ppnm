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
    std::cout << std::endl << std::endl;

    // Define x-range (real axis)
    double x_min = -5.0, x_max = 5.0;
    const int nx = 220;  // number of x points

    // Define user-chosen split points for the fine and coarse regions
    double y_coarse_min = -5.0, y_fine_min = -0.2;  // Coarse → Fine (negative side)
    double y_fine_max = 0.2, y_coarse_max = 5.0;    // Fine → Coarse (positive side)

    // Define the number of points in each segment
    const int n_coarse = 70;  // Points for coarse segments
    const int n_fine = 200;   // Points for fine segment

    // Create a vector to hold all y values.
    std::vector<double> y_values;
    
    // 1. Coarse segment: y from y_coarse_min to y_fine_min
    for (int i = 0; i < n_coarse; i++) {
        double y = y_coarse_min + (y_fine_min - y_coarse_min) * i / (n_coarse - 1);
        y_values.push_back(y);
    }
    
    // 2. Fine segment: y from y_fine_min to y_fine_max
    // Skip the first point to avoid duplicate y_fine_min
    for (int i = 1; i < n_fine; i++) {
        double y = y_fine_min + (y_fine_max - y_fine_min) * i / (n_fine - 1);
        y_values.push_back(y);
    }
    
    // 3. Coarse segment: y from y_fine_max to y_coarse_max
    // Skip the first point to avoid duplicate y_fine_max
    for (int i = 1; i < n_coarse; i++) {
        double y = y_fine_max + (y_coarse_max - y_fine_max) * i / (n_coarse - 1);
        y_values.push_back(y);
    }
    
    // Loop over the x and custom y grid.
    for (int i = 0; i < nx; i++) {
        double x = x_min + (x_max - x_min) * i / (nx - 1);
        for (double y : y_values) {
            std::complex<double> z(x, y);
            std::complex<double> gamma_val = sfuns::G(z);
            double abs_gamma = std::abs(gamma_val);
            double phase = std::atan2(gamma_val.imag(), gamma_val.real());
            // Output: real-part, imaginary-part, |Gamma(z)|, arg(Gamma(z))
            std::cout << x << " " << y << " " << abs_gamma << " " << phase << std::endl;
        }
        std::cout << "\n"; // Blank line separates rows for gnuplot's pm3d.
    }
}
