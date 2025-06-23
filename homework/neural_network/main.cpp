#include <iostream>
#include "ann.hpp"
#include <cmath>
#include <fstream>

// Function to approximate
double func(double x) {
    return std::cos(5*x-1)*std::exp(-x*x);
} 

int main() {

    std::cout << "Test" << std::endl;

    int n = 30;
    pp::vector xs(n), ys(n);

    for(int i =0; i<n;i++) {
        // interval always from -1 to 1 as defined in the ann
        double interval = 2.0/(n-1);
        xs[i] = -1+i*interval;
        ys[i] = func(-1+i*interval);
    }
    int hn = 5;
    std::cout << "Training newtork on " << hn << " hidden neurons over a sammpling interval -1 to 1 with "
              << n << " datapoints. Function to approximate is f(x) = cos(5*x-1)*e^(-x^2)" << std::endl;
    pp::ann nn(hn); // 10 hidden neurons
    // Train network on data
    nn.train(xs,ys);

    std::cout << "Training succesful" << std::endl;

    int n_new = 30;
    pp::vector xs_new(n_new);
    for(int i =0; i<n_new;i++) {
        // interval always from -1 to 1 as defined in the ann
        double interval = 2.0/(n_new-1);
        xs_new[i] = -1+i*interval;
    }

    std::ofstream file("ann_approximation.csv");
    if (!file.is_open()) {
        std::cerr << "Could not open " << "params.csv" << std::endl;
        return 1;
    }
    for(int i = 0; i<n_new;i++) {
        double x = xs_new[i];
        file << x << " "
             << func(x) << " "
             << nn.response(x) << " "
             << nn.response_derivative(x) << " "
             << nn.response_2nd_derivative(x) << " "
             << nn.response_integral(x) << "\n";
    }
    file.close();

    std::cout << "See function approximation in plot.ann.svg" << std::endl;

    return 0;
}