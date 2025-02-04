#include<cmath>
#include<chrono>
#include<iostream>
#include"includes/functions.hpp"

int main(){
    // largest signed & unsigned int number
    int x = 0;
    unsigned int y = 0;

    // largest signed int number
    for (int i = 2147482624; i>0; i++) {
        x = i;
        // This can be done since signed integers are being used
        if ((i+1)< 0) {
            break;
        }
    }
    // largest unsigned int number
    for (unsigned int i = x*2-2; i>0; i++) { 
        y = i;
        if ((i+1) < i ) {
            break;
        }
    }
    // machine epsilon
    float z = 0.01f;
    double t = 0.01;
    // find the machine epsilon for float
    while (1 + z != 1) {
        z /= 2;
    }
    // find the machine epsilon for double
    while (1 + t != 1) {
        t /= 2;
    }
    float f_epsilon = z*2;
    double d_epsilon = t*2;

    // tiny epsilon shenanigans
    float tiny = z;
    double tiny2 = t;
    float a_f = tiny + tiny + 1;
    double a_d = tiny2 + tiny2 + 1;
    float b_f = 1 + tiny + tiny;
    double b_d = 1 + tiny2 + tiny2; 

    // 1.0 eight times
    double d1 = 1.0101 + 1.0101 + 1.0101 + 1.0101 + 1.0101 + 1.0101 + 1.0101 + 1.0101;
    double d2 = 8*1.0101;

    // write to file
    std::cout << "largest signed int number: " << x << "\n";
    std::cout << "largest signed int number + 1:  " << x + 1 << "  This is also the smallest number due to the overflow wrap" << "\n";
    std::cout << "largest signed int number + 10: " << x + 10 << "\n";
    std::cout << "+1 larger or smaller? " << (x+1 > x ? "larger" : "smaller") << "\n";
    std::cout << "largest unsigned int number: " << y << "\n";
    std::cout << "largest unsigned int number + 1:  " << y+1 << "\n";
    std::cout << "largest unsigned int number + 10: " << y+10 << "\n";
    std::cout << "+1 larger or smaller? " << (y+1 > y ? "larger" : "smaller") << "\n";
    // more precision is needed to see the difference
    std::cout.precision(37);
    std::cout << "Machine float epsilon:  " << f_epsilon << "\n";
    std::cout << "Machine double epsilon: " << d_epsilon << "\n";
    std::cout << "(float) a = tiny + tiny + 1      =" << a_f << "\n";
    std::cout << "(double) a = tiny2 + tiny2 + 1   =" << a_d << "\n";
    std::cout << "(float) a_r = 1 + tiny + tiny    =" << b_f << "\n";
    std::cout << "(double) a_r = 1 + tiny2 + tiny2 =" << b_d << "\n";
    // check for "a==b", "a>1", "b>1"
    std::cout << "float a == float b:   " << (a_f == b_f ? "true" : "false") << "\n";
    std::cout << "double a == double b: " << (a_d == b_d ? "true" : "false") << "\n";
    std::cout << "float a > 1: " << (a_f > 1 ? "true" : "false") << "\n";
    std::cout << "double a > 1: " << (a_d > 1 ? "true" : "false") << "\n";
    std::cout << "float b > 1: " << (b_f > 1 ? "true" : "false") << "\n";
    std::cout << "double b > 1: " << (b_d > 1 ? "true" : "false") << "\n";
    std::cout << "I cannot explain the expressions with any security, i feel that the \"tiny\" epsilon should just be rounded to 0" << "\n";
    std::cout << "It seems as though the tiny epsilon can be added together as long as one is in the domain of their size" << "\n";
    // print d1 & d2 and check for d1 == d2
    std::cout << "d1: " << d1 << "\n";
    std::cout << "d2: " << d2 << "\n";
    std::cout << "d1 == d2: " << (d1 == d2 ? "true" : "false") << "\n";
    // print d1 & d2 and check for d1 == d2 using approx_equal
    std::cout << "d1 == d2 using approx_equal: " << (sdfuncs::approx_equal(d1, d2, 1e-9, d_epsilon) ? "true" : "false") << "\n";


    // Trying some simple time-it loops
    std::cout << "timed sdfuncs::absoluteValue value of -17.4: " << sdfuncs::timeit(sdfuncs::absoluteValue, -17.4) << " \u00B5s" << "\n";
    // since std::abs and std::fabs are overloaded, we need to specify the type, this is done by using a lambda function
    std::cout << "timed std::abs value of -17.4:               " << sdfuncs::timeit([](double x) { return std::abs(x); }, -17.4) << " \u00B5s" << "\n";
    std::cout << "timed std::fabs value of -17.4:              " << sdfuncs::timeit([](double x) { return std::fabs(x); }, -17.4) << " \u00B5s" << std::endl;

}