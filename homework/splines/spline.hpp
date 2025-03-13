#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "../includes/matrix.hpp"

namespace pp {

int binsearch(const pp::vector& x, double z);

struct lspline{
	pp::vector x,y;
	lspline(pp::vector xs, pp::vector ys) : x(xs), y(ys){};
    double linterp(const double z) const;
    double linterpInteg(const double z) const;
};

struct qspline{
	pp::vector x,y,b,c;
	qspline(pp::vector xs, pp::vector ys);
    double qinterp(const double z) const;
    double qinterpInteg(const double z) const;
    double qinterpDerivative(const double z) const;

};

struct cspline{
	pp::vector x,y,b,c,d;
	cspline(pp::vector xs, pp::vector ys);
    double cinterp(const double z) const;
    double cinterpInteg(const double z) const;
    double cinterpDerivative(const double z) const;

};

}

#endif // __SPLINE_H__