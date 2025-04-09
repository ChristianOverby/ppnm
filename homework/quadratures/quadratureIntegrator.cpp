#include "quadratureIntegrator.hpp"
#include <functional>
#include <cmath>
#include <tuple>
namespace pp
{
    std::tuple<double, double, int> integrate(const std::function<double(double)>& f, const double a, const double b, const double δ, const double ε, double f2, double f3, int evals)
    {
        //int evaluations = 0; // Initialize the evaluations count
        double h = b - a;
        if(std::isnan(f2)){ 
            f2=f(a+2*h/6);evals++; 
            f3=f(a+4*h/6);evals++; 
            } // first call, no points to reuse
        double f1=f(a+h/6); evals++;
        double f4=f(a+5*h/6); evals++;
        double Q = (2*f1+f2+f3+2*f4)/6*(b-a); // higher order rule
        double q = (  f1+f2+f3+  f4)/4*(b-a); // lower order rule
        double err =std::abs(Q-q);
        if (err <= δ + ε * std::abs(Q)) return std::make_tuple(Q, err, evals);
        else {
            auto first = integrate(f,a,(a+b)/2,δ/(std::sqrt(2)),ε,f1,f2);
            auto second = integrate(f,(a+b)/2,b,δ/(std::sqrt(2)),ε,f3,f4);
            double Q_endval = std::get<0>(first) + std::get<0>(second);
            double err_endval = std::get<1>(first) + std::get<1>(second);
            double evals_endval = evals + std::get<2>(first) + std::get<2>(second);
            return std::make_tuple(Q_endval, err_endval, evals_endval);
        }
    }
    
    std::tuple<double, double, int> CCintegrate(const std::function<double(double)>& f, const double a, const double b, const double δ, const double ε)
    {
        int evals = 0;
        std::function<double(double)> f_CC = [&f, a, b, &evals](double theta) {evals++;
            return f((a + b) / 2.0 + cos(theta) * (b - a) / 2.0) * sin(theta) * (b - a) / 2.0;};
        return integrate(f_CC, 0, M_PI, δ, ε, evals);

    }
    
    std::tuple<double, double, int> integrate_inf(const std::function<double(double)>& f, const double a, const double b, const double δ, const double ε)
    {
        std::function<double(double)> f_new;
        double a_new, b_new;
        if (std::isinf(a) && std::isinf(b)) {
        // Both bounds are infinite
        f_new = [f](double t) {
            double x = t / (1.0 - t * t);
            double dx_dt = (1.0 + t * t) / ((1.0 - t * t) * (1.0 - t * t));
            return f(x) * dx_dt;
        };
        a_new = -1.0 + 1e-10;
        b_new =  1.0 - 1e-10;

    } else if (std::isinf(a)) {
        // lower bound is infinite
        f_new = [f, b](double x) {
            double t = b + x / (1.0 + x);
            double dt_dx = 1.0 / ((1.0 + x) * (1.0 + x));
            return f(t) * dt_dx;
        };
        a_new = -1.0 + 1e-10;
        b_new = 0.0;

    } else if (std::isinf(b)) {
        // upper bound is infinite
        f_new = [f, a](double x) {
            double t = a + x / (1.0 - x);
            double dt_dx = 1.0 / ((1.0 - x) * (1.0 - x));
            return f(t) * dt_dx;
        };
        a_new = 0.0;
        b_new = 1.0 - 1e-10;

    } else {
        // Finite bounds
        f_new = f;
        a_new = a;
        b_new = b;
    }

    return integrate(f_new, a_new, b_new, δ, ε);
    }

    

}