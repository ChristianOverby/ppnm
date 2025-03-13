#ifndef __LSFITTER_H__
#define __LSFITTER_H__

#include "../includes/matrix.hpp"
#include <functional>
#include <utility>

namespace pp {

    std::pair<pp::vector, pp::matrix> ode_ls_fit(
        const std::vector<std::function<double(double)>>& fs, 
        const vector& x, 
        const vector& y, 
        const vector& dy);

}
#endif // __LSFITTER_H__