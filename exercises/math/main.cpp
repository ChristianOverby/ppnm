#include<iostream>
#include<cmath>
#include "includes/functions.h"

// main function

int main()
{   

    std::cout << "Some math function" << std::endl;

    // declare variables
    double pi = 3.14159;
    double sqrt2 = sqrt(2.0);
    double two_power1_5 = std::pow(2.0, 1.0/5.0);
    double e_power_pi = std::exp(M_PI);
    double pi_power_e = std::pow(pi, exp(1));

    // print the values
    std::cout << "The value of pi is: " << pi << '\n'; 
    std::cout << "The square root of 2 is: " << sqrt2 << '\n';
    std::cout << "2 raised to the power of 1/5 is: " << two_power1_5 << '\n';
    std::cout << "e raised to the power of pi is: " << e_power_pi << '\n';
    std::cout << "pi raised to the power of e is: " << pi_power_e << '\n';

    // Gamma function with n = 0 to n = 10
    for (double i = 0; i < 11; i++) {
        std::cout << "Gamma(" << i << ") = " << sfuns::fgamma(i) << "\n";
    }

    for (double i = 0; i < 11; i++) {
        std::cout << "lnGamma(" << i << ") = " << sfuns::lngamma(i) << "\n";
    }

    return 0;
}
