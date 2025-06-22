#ifndef __MINIMISER_H__
#define __MINIMISER_H__

#include "../includes/matrix.hpp"
#include <functional>

namespace pp {

    pp::vector gradient(std::function<double(const pp::vector&)> f, const pp::vector x);

    pp::matrix hessian(std::function<double(const pp::vector&)> f, const pp::vector x);
    
    std::pair<pp::vector, double> newton(std::function<double(const pp::vector&)> f ,pp::vector x,double acc=1e-3);
    
    

}


#endif // __MINIMISER_H__