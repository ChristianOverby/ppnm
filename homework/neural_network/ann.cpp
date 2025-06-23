#include "ann.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include "../minimisation/minimiser.hpp"




namespace pp
{
    ann::ann(int neurons) : n(neurons), a(neurons), b(neurons), w(neurons)
    {
        //Define some interval
        double start = -1.0, end = 1.0;
        for(int i = 0; i< neurons; i++) {
            a[i] = start + i*((end-start) / (n-1.0));
            b[i] = 0.5;
            w[i] = 2; 
        }
        f = [](double x) {return x*std::exp(-x*x);}; // Gaussian wavelet
        f_d = [](double x) {return (1-2*x*x)*std::exp(-x*x);}; // Gaussian wavelet derivative
        f_2d = [](double x) {return x*(3-2*x*x)*2*std::exp(-x*x);}; // Gaussian wavelet 2nd derivative
        f_i = [](double x) {return -1.0/2.0*std::exp(-x*x) +0.5;}; // Gaussian wavelet integral
     }

    double ann::response(double x)
    {
        double sum = 0;
        
        for(int i =0; i<n; i++) {
            double result = f((x-a[i])/b[i])*w[i];
            sum += result;
        }
        return sum;
    }
    
    double ann::response_derivative(double x)
    {
        double sum = 0;
        
        for(int i =0; i<n; i++) {
            double z = (x - a[i]) / b[i];
            double result = (w[i] / b[i]) * f_d(z); // Chain rule for correct expression
            sum += result;
        }
        return sum;
    }
    
    double ann::response_2nd_derivative(double x)
    {
        double sum = 0;
        
        for(int i =0; i<n; i++) {
            double z = (x - a[i]) / b[i];
            double result = w[i] / (b[i] * b[i]) * f_2d(z); // Again chain rule for correct expression
            sum += result;
        }
        return sum;
    }
    
    double ann::response_integral(double x)
    {
        double sum = 0;
        
        for(int i =0; i<n; i++) {
            double z = (x - a[i]) / b[i];
            double result = w[i] * b[i] * f_i(z); // From substituion
            sum += result;
        }
        return sum;
    }
    
    void ann::train(const pp::vector& x, const pp::vector& y)
    {
        // Unify parameters in one list since that is what my minimiser takes
        pp::vector start_params(n*3);
        for(int i = 0; i<n;i++) {
            start_params[i] = a[i];
            start_params[n+i] = b[i];
            start_params[2*n+i] = w[i];
        }

        // define the cost function
        std::function<double(const pp::vector&)> C_f = [&](const pp::vector& params) {
            for(int i = 0; i<n; i++) {
                a[i] = params[i];
                b[i] = params[i+n];
                w[i] = params[2*n+i];

            }
            double cost_sum = 0.0;
            for(int i = 0; i< x.size(); i++) {
                cost_sum += std::pow(response(x[i])-y[i],2);
            }
            return cost_sum;
        };
        // minimize the cost functions with a standard newton minimiser
        pp::vector params_minimised = pp::newton(C_f,start_params, 1e-3).first;
        // set the a, b and w vectors to the optimized params

        for(int i = 0; i<n; i++) {
            a[i] = params_minimised[i];
            b[i] = params_minimised[n+i];
            w[i] = params_minimised[2*n+i];
        }
    }
}