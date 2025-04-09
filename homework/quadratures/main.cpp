#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "quadratureIntegrator.hpp"

// wrapper to test functions


// Utility to compare and print results
void test_integration(
    const std::string& name,
    const std::function<double(double)>& f,
    double a,
    double b,
    double expected,
    double delta = 1e-8,
    double eps = 1e-8
) {
    auto [result, error_est, evals] = pp::integrate(f, a, b, delta, eps);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
    std::cout << "  Given ε    = " << eps << "\n";
    std::cout << "  Evaluations: " << evals << "\n";
    std::cout << (abs_error < eps ? "  Abs. Error < ε error\n\n" : "  Abs. Error > ε error\n") << std::endl;
}

// Utility to compare and print results
void test_integration_CC(
    const std::string& name,
    const std::function<double(double)>& f,
    double a,
    double b,
    double expected,
    double delta = 1e-8,
    double eps = 1e-8
) {
    auto [result, error_est, evals] = pp::CCintegrate(f, a, b, delta, eps);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
    std::cout << "  Given ε    = " << eps << "\n";
    std::cout << "  Evaluations: " << evals << "\n";
    
    std::cout << (abs_error < eps ? "  Abs. Error < ε error\n\n" : "  Abs. Error > ε error\n") << std::endl;
}

// Utility to compare and print results
void test_integration_inf(
    const std::string& name,
    const std::function<double(double)>& f,
    double a,
    double b,
    double expected,
    double delta = 1e-8,
    double eps = 1e-8
) {
    auto [result, error_est, evals] = pp::integrate_inf(f, a, b, delta, eps);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
    std::cout << "  Given ε    = " << eps << "\n";
    std::cout << "  Evaluations: " << evals << "\n";
    std::cout << (abs_error < eps ? "  Abs. Error < ε error\n\n" : "  Abs. Error > ε error\n") << std::endl;
}


// some functions
double f_sqrt(double x) {
        return std::sqrt(x);
    }

double f_sqrt_inv(double x) {
    return 1/(std::sqrt(x));
}

double f_half_circle(double x) {
    return 4*std::sqrt(1-x*x);
}

double f_ln_sqrt(double x) {
    return std::log(x)/std::sqrt(x);
}

const double ffactor_pi = 2/(std::sqrt(M_PI));

// Errofunction split into 2
// first part is for 0 <= Z <= 1
double erf_1(double z) {
    return ffactor_pi*std::get<0>(pp::integrate([](double x) {return std::exp(-(x*x));}, 0, z, 1e-9, 1e-9));
}
double erf_2(double z) {
    return 1-ffactor_pi*std::get<0>(pp::integrate([z](double t) {return std::exp(-std::pow(z+(1-t)/t,2))/(t*t);}, 0, 1, 1e-9, 1e-9));
}

double erf(double z) {
    if(z < 0) {
        return -erf(-z);
    }
    else if(z <= 1){
        return erf_1(z);
    }
    else {
        return erf_2(z);
    }
}




// Approximate errorfunction used in plot exercises
double erf_approx(double x){
    /// single precision error function (Abramowitz and Stegun, from Wikipedia)
    if (x<0)
        return -erf(-x);
    const double a[5] = {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
    double t = 1/(1+0.3275911*x);
    double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));/* the right thing */
    return 1-sum*std::exp(-x*x);
    } 



int main() {

    auto int_sqrt = pp::integrate(f_sqrt, 0.0, 1.0);

    auto int_sqrt_inv = pp::integrate(f_sqrt_inv, 0.0, 1.0);

    auto int_half_circle = pp::integrate(f_half_circle, 0.0, 1.0);

    auto int_ln_sqrt = pp::integrate(f_ln_sqrt, 0.0, 1.0);

    std::cout << "Integral of ∫_0^1 dx √(x) = " << std::get<0>(int_sqrt) << " Expected value: 2/3 " << "Absoulte error: " << std::abs(std::get<0>(int_sqrt) - 2.0/3.0) << std::endl;
    std::cout << "Integral of ∫_0^1 dx 1/√(x) = " << std::get<0>(int_sqrt_inv) << " Expected value: 2 " << "Absoulte error: " << std::abs(std::get<0>(int_sqrt_inv)-2.0) << std::endl;
    std::cout << "Integral of ∫_0^1 dx 4√(1-x²) = " << std::get<0>(int_half_circle) << " Expected value: π " << "Absoulte error: " << std::abs(std::get<0>(int_half_circle)- M_PI) << std::endl;
    std::cout << "Integral of ∫_0^1 dx ln(x)/√(x) = " << std::get<0>(int_ln_sqrt) << " Expected value: -4 " << "Absoulte error: " << std::abs(std::get<0>(int_ln_sqrt) + 4.0) << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    // save integration
    std::ofstream file("erf_int.csv");
    if(!file.is_open()) { std::cerr << "could not open erf_int.csv" << std::endl;}
    for (double i = -3; i<= 3; i += 0.1) {
        double val = erf(i);
        file << i << " " << val << std::endl;
    }
    file.close();

    //save approx
    file.open("erf_approx.csv");
    if(!file.is_open()) { std::cerr << "could not open erf_approx.csv" << std::endl;}
    for (double i = -3; i<= 3; i += 0.1) {
        double val = erf_approx(i);
        file << i << " " << val << std::endl;
    }
    file.close();
    
    // create differecnes between integrated values and approxiamte values with tabulated
    std::ifstream infile("erf_tab.csv");
    file.open("erf_difference.csv");

    

    double x, tab_erf;

    while(infile >> x >> tab_erf) {
        double intval = erf(x);
        double diff_int_ref = std::abs(intval- tab_erf);
        double diff_approx_ref = std::abs(erf_approx(x)-tab_erf);
        file << x << " " << diff_int_ref << " " << diff_approx_ref << std::endl; 
    }
    file.close();

    std::cout << "The error function implemented via its integral representation is plotted as plot.erf.svg" << std::endl;
    std::cout << "The accuracy comparison is plotted as plot.diff.svg" << std::endl;

    std::cout << "---------------------------------------------------------------------------------" << std::endl;
// Tests of normal integration method, with evaluations
    std::cout << "Some comparions between no transformation and Clenshaw–Curtis variable transformation \n";
    test_integration("Inverted Square root ∫_0^1 dx 1/√(x)",f_sqrt_inv, 0, 1, 2);
    test_integration_CC("Clenshaw–Curtis variable transformation integration of Inverted Square root ∫_0^1 dx 1/√(x)",f_sqrt_inv, 0, 1, 2);
    test_integration("ln over square root ∫x ln(x)/√(x) ",f_ln_sqrt, 0, 1, -4);
    test_integration_CC("Clenshaw–Curtis variable tran_0^1 dsformation of ln over square root ∫_0^1 dx ln(x)/√(x) ",f_ln_sqrt, 0, 1, -4, 1e-4);
    std::cout << "---------------------------------------------------------------------------------" << std::endl;

    // Gaussian integral
    std::cout << "Testing some infinite integrals" << std::endl;
    test_integration_inf("Gaussian ∫_inf^inf exp(-x^2)", [](double x) {
        return exp(-x * x);
    }, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), sqrt(M_PI));

    // Exponential decay
    test_integration_inf("Exponential decay ∫_inf^1 exp(-x)", [](double x) {
        return exp(-x);
    }, 0.0, std::numeric_limits<double>::infinity(), 1.0);

    // Inverse square
    test_integration_inf("Inverse square ∫_inf^inf 1 / (1 + x^2)", [](double x) {
        return 1.0 / (1.0 + x * x);
    }, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), M_PI);

    // Inverse square to 0
    test_integration_inf("Inverse square ∫_inf^0 1 / (1 + x^2)", [](double x) {
        return 1.0 / (1.0 + x * x);
    }, -std::numeric_limits<double>::infinity(), 0, M_PI/2);

    // Lorentzian peak
    test_integration_inf("Lorentzian ∫_-inf^inf 1 / (x^2 + 0.01)", [](double x) {
        return 1.0 / (x * x + 0.01);
    }, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), M_PI / sqrt(0.01));

    return 0;

}