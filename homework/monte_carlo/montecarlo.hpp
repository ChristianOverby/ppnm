#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__


#include <utility>
#include <functional>
#include <vector>
#include "../includes/matrix.hpp"


namespace pp {

std::pair<double, double> plainmc(std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N);

double corput(int n, int b);

void halton(int n, int d, double *points);

std::vector<int> generate_primes(int limit);

void lattice_rule(int n, int d, double *points);

std::pair<double, double> quasi_mc(std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N);

std::pair<double, double> strata_mc(
        std::function<double(pp::vector&)> f,
        const pp::vector& a,
        const pp::vector& b,
        int N,
        int n_min = 32);


}; // pp

#endif // __MONTECARLO_H__