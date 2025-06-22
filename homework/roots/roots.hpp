#ifndef __ROOTS_H__
#define __ROOTS_H__

#include "../includes/matrix.hpp"
#include "../linear_equations/QRGS.hpp"
#include <functional>
#include <cmath>

namespace pp {

pp::matrix jacobian(std::function<pp::vector(const pp::vector&)> f, pp::vector x, pp::vector fx = pp::vector(), pp::vector dx = pp::vector());

pp::vector newton(std::function<pp::vector(const pp::vector&)> f, pp::vector x, double eps = 1e-3, pp::vector = pp::vector());

using vfunc = std::function<vector(const vector&)>;
}
#endif // __ROOTS_H__