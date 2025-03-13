#include "spline.hpp"
#include <stdexcept>

namespace pp
{

    // Binary search to find the interval for z
    int binsearch(const pp::vector& x, double z)
    {/* locates the interval for z by bisection */ 
	if( z < x[0] || z > x[x.size() - 1] ) std::invalid_argument("binsearch: bad z");
	int i = 0, j = x.size() - 1;
	while(j-i > 1){
		int mid = (i+j) / 2;
		if(z > x[mid]) {i = mid;} else {j=mid;}
		}
	return i;
	}

    // Linear interpolation function
    double lspline::linterp(double z) const
    {
        int i=binsearch(x,z);
        double dx=x[i+1]-x[i]; if(!(dx>0)) std::invalid_argument("dx < 0?");
        double dy=y[i+1]-y[i];
        return y[i]+dy/dx*(z-x[i]);
    }
    
    // Integral of the linear spline from x[0] to z
    double lspline::linterpInteg(const double z) const
    {
        int i = binsearch(x,z);
        double integral = 0.0;

        // integrate until last point before z
        for (int j = 0; j < i; ++j) {
        double dx = x[j + 1] - x[j]; 
        double p_j = (y[j + 1] - y[j])/dx; // Slope in the interval [x[j], x[j+1]]
        integral += y[j] * dx + 0.5 * p_j*dx*dx;
        }

        // Compute the integral from x[i] to z
        double dx = z - x[i];
        double p_i = (y[i + 1] - y[i]) / (x[i + 1] - x[i]); // Slope in the interval [x[i], x[i+1]]
        
        integral += y[i] * dx + 0.5 * p_i*dx*dx;

        return integral;
    
    
    
    }
    
    qspline::qspline(pp::vector xs, pp::vector ys) : x(xs), y(ys), b(xs.size()), c(xs.size())
    {
        int n = x.size();
        // Compute differences between adjacent x-values (h) and slopes (p)
        pp::vector p(n-1), h(n-1); 
        for (int i = 0; i<n-1; i++) {
            h[i] = x[i+1]-x[i]; // Difference between adjacent x-values
            p[i] = (y[i+1] - y[i]) / h[i]; // Slope between adjacent points
            }
        
        // Compute the quadratic coefficients (c) using forward substitution
        // This step ensures continuity of the first derivative at the nodes
        for (int i = 0; i<n-2; i++) {c[i+1] = (p[i+1]-p[i]-c[i]*h[i])/h[i+1];}

        // Adjust the last quadratic coefficient to ensure smoothness
        c[n-2] /= 2.0;
        // Compute the quadratic coefficients (c) using backward substitution
        // This step ensures consistency and smoothness of the spline
        for (int i = n-3; i >=0; i--) {c[i] = (p[i+1]-p[i]-c[i+1]*h[i+1])/h[i];}
        
        // Compute the linear coefficients (b) for the quadratic spline
        for (int i = 0; i < n-1; i++) {b[i] = p[i] -c[i]*h[i];}
    }
    
    double qspline::qinterp(const double z) const
    {
        int i = binsearch(x, z);
        double dx = z - x[i];
        // Evaluate the quadratic spline at z -> Si(z) = y[i] + b[i] * dx + c[i] * dx^2 
        double val = y[i] + b[i] * dx + c[i] * dx * dx;
        return val;
    }
    
    double qspline::qinterpInteg(const double z) const
    {
        int i = binsearch(x, z);
        //Compute the integral up to x[i]
        double integral = 0;
        for (int j = 0; j < i; j++) {
            double dx = x[j+1]-x[j];
            // integral of qubic spline
            integral += y[j] * dx + (b[j] / 2) * dx * dx + (c[j] / 3) * dx * dx * dx;
        }
        // Compute the integral from x[i] to z
        double dx = z - x[i]; // Offset from x[i]
        integral += y[i] * dx + (b[i] / 2) * dx * dx + (c[i] / 3) * dx * dx * dx;

        return integral;
    }
    
    double qspline::qinterpDerivative(const double z) const
    {
        int i = binsearch(x, z);
        double dx = z - x[i];
        // return the derivative at z
        return b[i] + 2 * c[i] * dx;
    }

    cspline::cspline(pp::vector xs, pp::vector ys) : x(xs), y(ys), b(xs.size()), c(xs.size()), d(xs.size()-1) {
        
        int n = x.size();

        // differences between adjacent x-values (h) and slopes (p)        
        pp::vector p(n-1), h(n-1); 
        for (int i = 0; i<n-1; ++i) {
            h[i] = x[i+1]-x[i]; // Difference between adjacent x-values
            p[i] = (y[i+1] - y[i]) / h[i]; // Slope between adjacent points
            }

        // Tridiagonal system setup
        pp::vector alpha(n), beta(n), zeta(n), gamma(n);
        alpha[0] = 0; // Not used
        beta[0] = 2;
        zeta[0] = 0;
        gamma[0] = 0;

        for (int i = 1; i < n-1; ++i) {
            alpha[i] = 3.0 * (p[i] - p[i - 1]);
            beta[i] = 4.0 - zeta[i - 1];
            zeta[i] = 1.0 / beta[i];
            gamma[i] = (alpha[i] - gamma[i - 1]) / beta[i];
        }

        beta[n-1] = 1;
        gamma[n-1] = 0;
        c[n-1] = 0;

        // Back substitution
        for (int i = n-2; i >= 0; --i) {
            c[i] = (gamma[i] - zeta[i] * c[i+1]);
        }

        // Compute b and d coefficients
        for (int i = 0; i < n-1; ++i) {
            b[i] = p[i] - h[i] * (2 * c[i] + c[i+1]) / 3;
            d[i] = (c[i+1] - c[i]) / (3 * h[i]);
        }
    }

    double cspline::cinterp(const double z) const {
        int i = binsearch(x, z);
        double dx = z - x[i];
        return y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
    }
    
    double cspline::cinterpInteg(const double z) const {
        int i = binsearch(x, z);
        double integral = 0;
        //Compute the integral up to x[i]
        for (int j = 0; j < i; j++) {
            double dx = x[j+1] - x[j];
            integral += y[j]*dx + b[j]* dx*dx/2 + c[j] *dx*dx*dx/3 + d[j] *dx*dx*dx*dx/4;
        }
        // Compute the integral from x[i] to z
        double dx = z - x[i];
        integral += y[i]*dx + b[i]* dx*dx/2 + c[i] *dx*dx*dx/3 + d[i] *dx*dx*dx*dx/4;;
        return integral;
    }

    
    double cspline::cinterpDerivative(const double z) const {
        int i = binsearch(x, z);
        double dx = z - x[i];
        return b[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
    }


}