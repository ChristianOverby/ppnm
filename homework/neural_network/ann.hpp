#ifndef __ANN_H__
#define __ANN_H__

#include <functional>
#include "../includes/matrix.hpp"

namespace pp {
    
    class ann {
        private:
        int n; // number of neurons
        pp::vector a,b,w; // network parameter-vector p constituents
        std::function<double(double)> f; // Activation function
        // Now also include the derivative, 2nd derivative and the integral
        std::function<double(double)> f_d;
        std::function<double(double)> f_2d;
        std::function<double(double)> f_i;

        public:
        ann(int n);
        double response(double x);
        double response_derivative(double x);
        double response_2nd_derivative(double x);
        double response_integral(double x);
        void train(const pp::vector& x, const pp::vector& y);
    };


}


#endif // __ANN_H__