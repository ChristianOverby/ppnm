#include <complex>
#include <iostream>

bool approx(const std::complex<double>& a, const std::complex<double>& b, double eps = 1e-6) {
    return std::abs(a - b) < eps;
}

int main() 
{
    // Define the imaginary unit.
    const std::complex<double> I(0, 1);

    // 1. sqrt(-1):
    const std::complex<double> sqrt_minus1 = std::sqrt(std::complex<double>(-1,0));
    const std::complex<double> sqrt_minus1_expected_value = std::complex<double>(0,1);    
    std::cout << "sqrt(-1) = " << sqrt_minus1 << "\t" << "Expected value = " << sqrt_minus1_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(sqrt_minus1, sqrt_minus1_expected_value) ? "true" : "false") << std::endl; 
    std::cout << std::endl;
    // 2. sqrt(i)
    const std::complex<double> sqrt_i = std::sqrt(I);
    const std::complex<double> sqrt_i_expected_value(1/std::sqrt(2), 1/std::sqrt(2));
    std::cout << "sqrt(i) = " << sqrt_i << "\t" << "Expected value = " << sqrt_i_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(sqrt_i, sqrt_i_expected_value) ? "true" : "false") << std::endl; 
    std::cout << std::endl;
    // 3. e^i
    const std::complex<double> exp_i = std::exp(I);
    const std::complex<double> exp_i_expected_value(std::cos(1), std::sin(1));
    std::cout << "exp(i) = " << exp_i << "\t" << "Expected value = " << exp_i_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(exp_i, exp_i_expected_value) ? "true" : "false") << std::endl; 
    std::cout << std::endl;
    // 4. e^(i pi)
    const std::complex<double> exp_i_pi = std::exp(I*M_PI);
    const std::complex<double> exp_i_pi_expected_value(-1, 0);
    std::cout << "exp(i*pi) = " << exp_i_pi << "\t" << "Expected value = " << exp_i_pi_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(exp_i_pi, exp_i_pi_expected_value) ? "true" : "false") << std::endl; 
    std::cout << std::endl;
    // 5. i^i
    const std::complex<double> I_I = std::pow(I, I);
    const std::complex<double> I_I_expected_value = std::exp(-M_PI/2);
    std::cout << "i^i = " << I_I << "\t" << "Expected value = " << I_I_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(I_I, I_I_expected_value) ? "true" : "false") << std::endl;
    std::cout << std::endl;
    // 6. ln(i)
    const std::complex<double> ln_i = std::log(I);
    const std::complex<double> ln_i_expected_value(0, M_PI/2);
    std::cout << "ln(i) = " << ln_i << "\t" << "Expected value = " << ln_i_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(ln_i, ln_i_expected_value) ? "true" : "false") << std::endl; 
    std::cout << std::endl;
    // 7. sin(i*pi)
    const std::complex<double> sin_i_pi = std::sin(I*M_PI);
    const std::complex<double> sin_i_pi_expected_value = I * std::sinh(M_PI);
    std::cout << "sin(i*pi) = " << sin_i_pi << "\t" << "Expected value = " << sin_i_pi_expected_value << std::endl;
    std::cout << "Approx equal: " << (approx(sin_i_pi, sin_i_pi_expected_value) ? "true" : "false") << std::endl; 


}

