#include "vec.hpp"
#include <string>
namespace udvector {
        // constructors
        vec::vec() : x(0), y(0), z(0) {}
        vec::vec(const double xCon, const double yCon, const double zCon) : x(xCon), y(yCon), z(zCon) {}

        // getters
        double vec::getX() const {
            return x;
            }
        double vec::getY() const {
            return y;
            }
        double vec::getZ() const {
            return z;
            }
        
        // setters
        void vec::setX(const double xCon) {
            x = xCon;
        }
        void vec::setY(const double yCon) {
            y = yCon;
        }
        void vec::setZ(const double zCon) {
            z = zCon;
        }

        // operator
        vec vec::operator+(const vec& v) const {
            return vec(x+v.x, y + v.y, z+ v.z);
        }
        vec vec::operator-(const vec& v) const {
            return vec(x-v.x, y - v.y, z- v.z);
        }
        vec vec::operator-() const {
            return vec(-x, -y, -z);
        }
        vec vec::operator*(const double& c) const {
            return vec(x*c, y*c, z*c);
        }
        std::string vec::toString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }
    // Non-member operator for scalar multiplication (c * v)
    vec operator*(const double& c, const vec& v) {
        return vec(v.x*c, v.y*c, v.z*c);
    }
}