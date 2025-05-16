#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include "montecarlo.hpp"
#include "../includes/matrix.hpp"
// circle
// f(x, y) = 1 if x^2+y^2 < 1^2
double circle(const pp::vector& v) {
        return (v[0]*v[0]+v[1]*v[1]) <= 1 ? 1.0 : 0;
}
double triangle(const pp::vector& v) {
    return (v[0] + v[1] <=1 ? 1 : 0);
}
double watson_integral(const pp::vector& v) {
    double cx = std::cos(v[0]);
    double cy = std::cos(v[1]);
    double cz = std::cos(v[2]);
    double bar = (cx * cy * cz);
    if (bar == 1) return 0; // no 0 div pls
    return 1.0 / (1.0 - bar);
}


void test_plainmc(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::plainmc(f, a, b, N);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}

void test_quasimc(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::quasi_mc(f, a, b, N);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}

void test_stratamc(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::strata_mc(f, a, b, N);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}


void test_plainmcWatson(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::plainmc(f, a, b, N);
    result *= 1/(M_PI*M_PI*M_PI);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}

void test_quasimcWatson(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::quasi_mc(f, a, b, N);
    result *= 1/(M_PI*M_PI*M_PI);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}
void test_stratamcWatson(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, double expected) {
    auto [result, error_est] = pp::strata_mc(f, a, b, N);
    result *= 1/(M_PI*M_PI*M_PI);
    double abs_error = std::abs(result - expected);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Test: " << name << "\n";
    std::cout << "  Result     = " << result << "\n";
    std::cout << "  Expected   = " << expected << "\n";
    std::cout << "  Abs Error  = " << abs_error << "\n";
    std::cout << "  Est. Error = " << error_est << "\n";
}

void gen_plainmc(const std::string& name,std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N, const double expected) {
    
    std::ofstream file(name);
    file << "N" << " " << "result" << " " << "est. error" << " " << "abs. error\n"; 
    
    for(int i = 100; i<=N; i+=200) {
        auto [result, error_est] = pp::plainmc(f, a, b, i);
        double abs_error = std::abs(result - expected);
        file << i << " " << result << " " << error_est << " " << abs_error << "\n";
    }
    file.close();
}

int main() {

    pp::vector circle_up_bounds(2), circle_low_bounds(2);
    circle_up_bounds[0] = 1, circle_up_bounds[1] = 1; 
    circle_low_bounds[0] = -1, circle_low_bounds[1] = -1;

    pp::vector triangle_lb(2), triangle_ub(2);
    triangle_lb[0] = 0, triangle_lb[1] = 0;
    triangle_ub[0] = 1, triangle_ub[1] = 1;

    pp::vector watson_lb(3), watson_ub(3);
    watson_lb[0] = 0;     watson_ub[0] = M_PI;
    watson_lb[1] = 0;     watson_ub[1] = M_PI;
    watson_lb[2] = 0;     watson_ub[2] = M_PI;

    double N = 50000;
    std::cout << "Testing some relevant functions" << std::endl;
    test_plainmc("test plainmc circle integration", circle, circle_low_bounds, circle_up_bounds, N, M_PI);
    test_quasimc("test quacimc circle integration", circle, circle_low_bounds, circle_up_bounds, N, M_PI);
    test_stratamc("test stratamc circle integration", circle, circle_low_bounds, circle_up_bounds, N, M_PI);
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    test_plainmc("test plainmc triangle integration", triangle, triangle_lb, triangle_ub, N, 1.0/2.0);
    test_quasimc("test quasinmc triangle integration", triangle, triangle_lb, triangle_ub, N, 1.0/2.0);
    test_stratamc("test stratamc triangle integration", triangle, triangle_lb, triangle_ub, N, 1.0/2.0);
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    test_plainmcWatson("test plainmc Watson integration", watson_integral, watson_lb, watson_ub, N*10, 1.3932039296856768591842462603255);
    test_quasimcWatson("test quasimc Watson integration", watson_integral, watson_lb, watson_ub, N*10, 1.3932039296856768591842462603255);
    test_stratamcWatson("test stratamc Watson integration", watson_integral, watson_lb, watson_ub, N*10, 1.3932039296856768591842462603255);



    gen_plainmc("plainmc_unit_cirle.csv", circle, circle_low_bounds, circle_up_bounds, N, M_PI);
    gen_plainmc("plainmc_triangle.csv", triangle, triangle_lb, triangle_ub, N, 1.0/2.0);
    return 0;
}