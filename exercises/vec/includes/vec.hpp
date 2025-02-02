#ifndef VEC_HPP
#define VEC_HPP

#include <string>

namespace udvector {
    class vec {
    private:
        double x,y,z;

    public:
        //constructors
        vec();
        vec(const double xCon, const double yCon, const double zCon);

        //getters
        double getX() const;
        double getY() const;
        double getZ() const;

        //setters
        void setX(const double xCon);
        void setY(const double yCon);
        void setZ(const double zCon);

        //operators
        friend vec operator*(const double& c, const vec& v);

        vec operator+(const vec& v) const;
        vec operator-(const vec& v) const;
        vec operator-() const;
        vec operator*(const double& c) const;

        double dot(const vec& v) const;
        vec static dot(const vec& v1, const vec& v2);
        vec cross(const vec& v) const; 

        std::string toString() const;
    };
    // Non-member operator for scalar multiplication (c * v)
    vec operator*(const double& c, const vec& v);
}

#endif // VEC_HPP