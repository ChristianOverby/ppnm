#include <iostream>
#include <cmath>
#include <fstream>
#include "odeint.hpp"

// Vector that represents the system of ODEs (Harmonic oscillator)
pp::vector harm_oscillator(double x, const pp::vector& y) {
    pp::vector vec(2);
    vec[0] = y[1];        // y' = v
    vec[1] = -y[0];       // v' = -y
    return vec;
}
// vector function of lotka-volterra system
// x' = a*x - b*x*y
// y' = d*x*y - g*y
pp::vector lotka_volterra(double x, const pp::vector& y) {
    // Parameters
    double alpha = 1.5;  // Prey growth rate
    double beta = 1;   // Predation rate
    double gamma = 3;  // Predator death rate
    double delta = 1;  // Predator growth rate

    // Extract state variables
    double x_pop = y[0];  // Prey population
    double y_pred = y[1];  // Predator population

    pp::vector vec(2);
    vec[0] = alpha*x_pop-beta*x_pop*y_pred;              // x' = a*x - b*x*y
    vec[1] = delta * x_pop * y_pred - gamma * y_pred;    // y' = d*x*y - g*y
    return vec;
}

// Vector that represents the system of ODEs (Oscillator with friction)
// theta''(t) + b*theta'(t) + c*sin(theta(t)) = 0 =>
// theta'(t) = omega(t)
// omega'(t) = -b*omega(t) - c*sin(theta(t))
pp::vector damped_oscillator(double t, const pp::vector& y) {
    double b = 0.25;
    double c = 5.0;
    pp::vector dydt(2);
    double theta = y[0];
    double omega = y[1];
    dydt[0] = omega;                     
    dydt[1] = -b*omega - c*std::sin(theta);   
    return dydt;
}

// equatorial motion of a planet around a star in General Relativity.
// u''(φ) + u(φ) = 1 + εu(φ)2 ,
// u(φ)' = v(φ)
// v'(φ) = εu(φ)2 + 1 - u(φ)
pp::vector eq_motion(double phi, const pp::vector& y, const double epsilon) 
{
    pp::vector dydphi(2);
    double u = y[0];  // u(φ)
    double v = y[1];  // v(φ) = u'(φ)
    dydphi[0] = v;
    dydphi[1] = epsilon*u*u+1-u;
    return dydphi;
}

// Newton gravitational three body diagram
pp::vector three_body_problem(double t, const pp::vector& z)
{
    double vx1 = z[0], vy1 = z[1];
    double vx2 = z[2], vy2 = z[3];
    double vx3 = z[4], vy3 = z[5];

    double x1 = z[6], y1 = z[7];
    double x2 = z[8], y2 = z[9];
    double x3 = z[10], y3 = z[11];

    double dx12 = x2 - x1, dy12 = y2 - y1;
    double dx13 = x3 - x1, dy13 = y3 - y1;
    double dx23 = x3 - x2, dy23 = y3 - y2;

    double r12 = std::pow(dx12 * dx12 + dy12 * dy12, 1.5);
    double r13 = std::pow(dx13 * dx13 + dy13 * dy13, 1.5);
    double r23 = std::pow(dx23 * dx23 + dy23 * dy23, 1.5);

    pp::vector dzdt(12);  // Derivative vector

    dzdt[0] = dx12 / r12 + dx13 / r13;  // dvx1/dt
    dzdt[1] = dy12 / r12 + dy13 / r13;  // dvy1/dt
    dzdt[2] = -dx12 / r12 + dx23 / r23;  // dvx2/dt
    dzdt[3] = -dy12 / r12 + dy23 / r23;  // dvy2/dt
    dzdt[4] = -dx13 / r13 - dx23 / r23;  // dvx3/dt
    dzdt[5] = -dy13 / r13 - dy23 / r23;  // dvy3/dt

    // Velocities (dr/dt = v)
    dzdt[6] = vx1;  // dx1/dt
    dzdt[7] = vy1;  // dy1/dt
    dzdt[8] = vx2;  // dx2/dt
    dzdt[9] = vy2;  // dy2/dt
    dzdt[10] = vx3;  // dx3/dt
    dzdt[11] = vy3;  // dy3/dt

    return dzdt;
}


int main() {

    pp::vector HO_cond(2);
    HO_cond[0] = 1; // y(0) = 1
    HO_cond[1] = 0; // y(1) = 0

    auto HO_solved = pp::driver(harm_oscillator,0, 2*M_PI, HO_cond, 0.01, 1e-7, 1e-7,1000);

    std::ofstream file("harmosc.csv");
    if(!file.is_open()) {
        std::cerr << "Couldn't open file" << std::endl; return 1;
    }
    file << "x y v\n";
    for(int i =0; i< HO_solved.first.size(); i++) {
        file << HO_solved.first[i] << " " << HO_solved.second[i] << " " << std::endl;
    }

    file.close();

    pp::vector LV_cond(2);
    LV_cond[0] = 10;
    LV_cond[1] = 5;

    auto LV_solved = pp::driver(lotka_volterra, 0, 15, LV_cond, 0.01, 1e-7, 1e-7,1000);

    file.open("lotkaVolterra.csv");
    if(!file.is_open()) {
        std::cerr << "Couldn't open file" << std::endl; return 1;
    }
    file << "x y v\n";
    for(int i =0; i< LV_solved.first.size(); i++) {
        file << LV_solved.first[i] << " " << LV_solved.second[i] << " " << std::endl;
    }

    file.close();

    // Create the interpolant
    auto interpolant = make_ode_ivp_interpolant(lotka_volterra, 0, 15, LV_cond, 0.01, 1e-7, 1e-7,1000);

    file.open("lotkaVolterraInterpolated.csv");
    file << "t x y" << std::endl;
    // Evaluate the interpolant at arbitrary points
    for (double t = 0.0; t <= 15; t += 0.01) {
        pp::vector y = interpolant(t);
        file << t << " " << y[0] << " " << y[1] << std::endl;
    }

    file.close();


    pp::vector dampedOsc_cond(2);
    dampedOsc_cond[0] = M_PI-0.1;
    dampedOsc_cond[1] = 0;

    auto DO_solved = pp::driver(damped_oscillator, 0, 10, dampedOsc_cond, 0.01, 1e-7, 1e-7,1000);

    file.open("dampedOscillations.csv");
    if(!file.is_open()) {
        std::cerr << "Couldn't open file" << std::endl; return 1;
    }
    file << "x y v\n";
    for(int i =0; i< DO_solved.first.size(); i++) {
        file << DO_solved.first[i] << " " << DO_solved.second[i] << " " << std::endl;
    }

    file.close();

    // Open file for saving results
    file.open("orbits.csv");
    if (!file.is_open()) {
        std::cerr << "Couldn't open file" << std::endl;
        return 1;
    }

    // Write header
    file << "phi,u_circular,v_circular\n";

    double atol = 1e-12;
    double rtol = 1e-12;
    // Scenario 1: Newtonian Circular Motion (ε = 0, u(0) = 1, u'(0) = 0)
    pp::vector y0_circular(2);
    y0_circular[0] = 1.0;
    y0_circular[1] = 0.0;
    auto circular_solution = pp::make_ode_ivp_interpolant([&](double phi, const pp::vector& y){ return eq_motion(phi, y, 0.0); },
        0.0, 2 * M_PI, y0_circular, 0.001, atol, rtol, 10000
    );


    // Scenario 1: Newtonian Circular Motion (ε = 0, u(0) = 1, u'(0) = 0)
    pp::vector y0_elliptical(2);
    y0_elliptical[0] = 1.0;
    y0_elliptical[1] = -0.5;
    auto elliptical_solution = pp::make_ode_ivp_interpolant([&](double phi, const pp::vector& y){ return eq_motion(phi, y, 0.0); },
        0.0, 12 * M_PI, y0_elliptical, 0.001, atol, rtol, 10000
    );

    pp::vector y0_relativistic(2);
    y0_relativistic[0] = 1.0;
    y0_relativistic[1] = -0.5;
    auto relativistic_solution = pp::make_ode_ivp_interpolant([&](double phi, const pp::vector& y){ return eq_motion(phi, y, 0.01); },
        0.00, 12 * M_PI, y0_relativistic, 0.001, atol, rtol, 100000
    );

    // Evaluate the interpolant at arbitrary points
    for (double t = 0.0; t <= 12*M_PI; t += 0.01) {
        pp::vector y = circular_solution(t);
        pp::vector y_e = elliptical_solution(t);
        pp::vector y_r = relativistic_solution(t);
        file << t << " " << y[0] << " " << y_e[0] << " " << y_r[0] << std::endl;
    }

    file.close();

    pp::vector z0(12);

    // Initial positions
    z0[6] = -0.97000436;  // x1
    z0[7] = 0.24308753;   // y1
    z0[8] = 0.97000436;   // x2
    z0[9] = -0.24308753;  // y2
    z0[10] = 0.0;         // x3
    z0[11] = 0.0;         // y3

    // Initial velocities
    z0[0] = 0.466203685;  // vx1
    z0[1] = 0.43236573;   // vy1
    z0[2] = 0.466203685;  // vx2
    z0[3] = 0.43236573;   // vy2
    z0[4] = -0.93240737;  // vx3
    z0[5] = -0.86473146;  // vy3

    // Time range: t = [0, 10]
    double t0 = 0.0;
    double t_end = 10.0;
    atol = atol;
    rtol = rtol;

    auto tbd = pp::make_ode_ivp_interpolant(three_body_problem, t0, t_end, z0, 0.01, atol, rtol);

    file.open("threeBodyProblem.csv");
    if (!file.is_open()) {
        std::cerr << "Couldn't open file" << std::endl;
        return 1;
    }
    file << "t,x1,y1,x2,y2,x3,y3\n";
    for(double i =0; i<=6.3259/3; i += 0.001) {
        pp::vector tmp = tbd(i);
        file << i << " "
             << tmp[6] << " " << tmp[7] << " "
             << tmp[8] << " " << tmp[9] << " "
             << tmp[10] << " " << tmp[11] << "\n";
    }

    file.close();

    return 0;
}