#include <iostream>
#include <cmath>
#include <fstream>
#include <utility>
#include "roots.hpp"
#include "../ode/odeint.hpp"

// Simple 1D function f(x) = 5*sqrt(x) - 10
pp::vector S1D(pp::vector x) {
    pp::vector f(1);
    f[0] = 5*std::sqrt(x[0]) - 10;
    return f;
}

// Simple 2D equation x + y = 5, 2x - y = 10 
pp::vector S2D(pp::vector x) {
    pp::vector f(2);
    f[0] = x[0]+x[1] - 5;
    f[1] = 2*x[0]-x[1] - 10;
    return f;
}


// Graident of the rosenbrock function f(x,y) = (1-x)^2+100(y-x^2)^2
pp::vector rosenbrock(pp::vector x) {
    pp::vector g(2); // The gradient as vector ∇f(x,y) = (∂x/∂f, ∂y/∂f)
    g[0] = -2*(1 - x[0]) - 400*x[0]*(x[1] - x[0]*x[0]); // ∂x/∂f = −2(1−x)−400x(y−x^2)
    g[1] = 200*(x[1] - x[0]*x[0]);                                      // ∂y/∂f = 200(y−x^2)
 
    return g;
}

// Hyrdogen atom

// Schrödinger wave function in digestible 1st-order ODE system
// f' = g
// g' = f'' = -2*(E+1/r)*f
pp::vector schrodinger(pp::vector f, double E, double r) {
    pp::vector g(2);
    g[0] = f[1];
    g[1] = -2*(E+1/r)*f[0];
    return g;
}

// Auxillary function M(E) = f_E(rmax). (f being the function in the ODE system)
// in vector style for newton method
pp::vector M(pp::vector E, double rmin, double rmax, double acc, double eps) {
    // Initial condition based on near-origin behavior: f(rmin) = r - r², f'(rmin) = 1 - 2r
    pp::vector ystart(2);
    ystart[0] = rmin - pow(rmin, 2);
    ystart[1] = 1 - 2 * rmin;
    
    // Solve with ode_integrator implemented earlier.

    std::function<pp::vector(double, const pp::vector&)> F = [&](double r, const pp::vector& y){return schrodinger(y,E[0], r);};

    std::pair<pp::vector, std::vector<pp::vector>> result = pp::driver(F,rmin, rmax,ystart,acc, eps);
    double f_at_rmax = result.second.back()[0];

    pp::vector bar(1);
    bar[0] = f_at_rmax;
    return bar;
}


int main() {

    pp::vector guess, root;

    // 1D eq.
    std::cout << "Part 1: \n" << std::endl;

    guess = pp::vector(1);
    std::cout << "Testing 1D function 5√x + 10" << std::endl;
    guess[0] = 0;
    root = pp::newton(S1D, guess);
    std::cout << "Guess: " << guess[0] << ", root at: " << root[0] << std::endl;
    guess[0] = 2;
    root = pp::newton(S1D, guess);
    std::cout << "Guess: " << guess[0] << ", root at: " << root[0] << std::endl;
    guess[0] = 4;
    root = pp::newton(S1D, guess);
    std::cout << "Guess: " << guess[0] << ", root at: " << root[0] << std::endl;
    guess[0] = 6;
    root = pp::newton(S1D, guess);
    std::cout << "Guess: " << guess[0] << ", root at: " << root[0] << std::endl;

    // 2d eq.
    guess = pp::vector(2);
    std::cout << "Testing 2D linear equation x + y = 5, 2x - y = 10" << std::endl;
    guess[0] = 0;
    guess[1] = 0;
    root = pp::newton(S2D, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess[0] = -2;
    guess[1] = -2;
    root = pp::newton(S2D, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess[0] = 2;
    guess[1] = 2;
    root = pp::newton(S2D, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess[0] = -2;
    guess[1] = 2;
    root = pp::newton(S2D, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    
    // Rosenbrock
    guess = pp::vector(2);
    std::cout << "Testing Rosenkbrock roots" << std::endl;
    guess[0] = 0;
    guess[1] = 0;
    root = pp::newton(rosenbrock, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess = pp::vector(2);
    std::cout << "Testing Rosenkbrock roots" << std::endl;
    guess[0] = -2;
    guess[1] = -2;
    root = pp::newton(rosenbrock, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess = pp::vector(2);
    std::cout << "Testing Rosenkbrock roots" << std::endl;
    guess[0] = 2;
    guess[1] = 2;
    root = pp::newton(rosenbrock, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;
    guess = pp::vector(2);
    std::cout << "Testing Rosenkbrock roots" << std::endl;
    guess[0] = -2;
    guess[1] = 2;
    root = pp::newton(rosenbrock, guess);
    std::cout << "Guess: " << guess << ", root at: " << root << std::endl;

    std::cout << "\nPart 2: \n" << std::endl;

    // Hydrogen atom
    // Guess for the Energy. I just use a negative number
    guess = pp::vector(1); guess[0] = -1;
    pp::vector E0;  auto v = [&](pp::vector E) { return M(E, 1e-4, 8, 0.001, 0.001); };
    E0 = pp::newton(v, guess);
    std::cout << "Lowest energy E0(rmax=8) = " << E0 << std::endl;

    // Solve the hydorgen wavefunction ODE at E0
    pp::vector ystart(2);
    double rmin = 1e-4, rmax = 8.0;
    ystart[0] = rmin - pow(rmin, 2);
    ystart[1] = 1 - 2 * rmin;
    

    // Solve with ode_integrator for custom pointspacing.
    auto F = [&](double r, const pp::vector& y) { return schrodinger(y, E0[0], r); };

    // Create an interpolant for the solution
    std::function<pp::vector(double)> interpolant = pp::make_ode_ivp_interpolant(F, rmin, rmax, ystart, 0.001, 0.001, 0.001, 1000);

    // Export interpolated wavefunction data
    std::ofstream file("wavefunction_interpolated.csv");
    double step = 0.3; // Smaller step size for interpolation
    for (double r = rmin; r <= rmax; r += step) {
        pp::vector interpolated = interpolant(r);
        file << r << " " << interpolated[0] << "\n"; // Export r and the first component of the interpolated solution
    }
    file.close();
    // Convergence analysis
    int n = 50;
    pp::vector rminList(n), rmaxList(n), accList(n), epsList(n);
    pp::vector Δrmin(n), Δrmax(n), Δacc(n), Δeps(n);

    for(int i =0; i<n; i++) {
        rmaxList[i] = i/5.0 + 1;
        rminList[i] =  1.0 - (i/5.0 * 0.1);      // inverse countdown
        accList[i] = 1 / (std::pow(2, i/5.0)); // logarithmic dropoff
        epsList[i] = 1 / (std::pow(2, i/5.0)); // logarithmic dropoff
    }

    // Energy list
    for(int i = 0; i<n; i++) {
        guess = pp::vector(1); guess[0] = -1;
        auto v1 = [&](pp::vector E) { return M(E, rminList[i], 8, 0.001, 0.001); };
        Δrmin[i] = pp::newton(v1, guess)[0];
        auto v2 = [&](pp::vector E) { return M(E, 1e-4, rmaxList[i], 0.001, 0.001); };
        Δrmax[i] = pp::newton(v2, guess)[0];
        auto v3 = [&](pp::vector E) { return M(E, 1e-4, 8, accList[i], 0.001); };
        Δacc[i] = pp::newton(v3, guess)[0];
        auto v4 = [&](pp::vector E) { return M(E, 1e-4, 8, 0.001, epsList[i]); };
        Δeps[i] = pp::newton(v4, guess)[0];
    }

    // Export convergence data
    file.open("convergence.csv");
    for (int i = 0; i < n; i++) {
        file << rminList[i] << " " << rmaxList[i] << " " << accList[i] << " " << epsList[i] << " "
             << Δrmin[i]    << " " << Δrmax[i]    << " " << Δacc[i]    << " " << Δeps[i]    << "\n";
    }
    file.close();

    std::cout << "Note that the convergence of eps and acc is bounded by each other in this case 0.01" << std::endl;


}