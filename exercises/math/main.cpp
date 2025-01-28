#include<iostream>
#include<cmath>

// main function

int main()
{
    // declare variables
    double pi = 3.14159;
    double sqrt2 = sqrt(2);
    double two_power1_5 = std::pow(2, 1/5);
    double e_power_pi = std::exp(M_PI);
    double pi_power_e = std::pow(pi, exp(1));

    // print the values
    std::cout << "The value of pi is: " << pi << '\n'; 
    std::cout << "The square root of 2 is: " << sqrt2 << '\n';
    std::cout << "2 raised to the power of 1/5 is: " << two_power1_5 << '\n';
    std::cout << "e raised to the power of pi is: " << e_power_pi << '\n';
    std::cout << "pi raised to the power of e is: " << pi_power_e << '\n';
}


