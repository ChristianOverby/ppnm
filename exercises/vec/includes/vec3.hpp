#ifndef VEC3_HF
#define VEC3_HF

#include <string>
#include <iostream>
#include "functions.hpp"
namespace udvector {

    template <typename T>
    class vec3 {
        public:
            T x,y,z;

            // constructor
            vec3() : x(0), y(0), z(0) {};
            vec3(const T& x_set, const T& y_set, const T& z_set) : x(T(x_set)), y(T(y_set)), z(T(z_set)) {};
            
            // Let the compiler generate these since that would be completely fine for statically allocated memory
            vec3(const vec3&) = default;        // Copy constructor
            vec3(vec3&&) = default;             // Move constructor
            vec3& operator=(const vec3&) = default;  // Copy assignment
            vec3& operator=(vec3&&) = default;       // Move assignment
            ~vec3() = default;                  // Destructor

            // operators
            // +
            vec3 operator+(const vec3& v) const {return vec3(v.x + x, v.y + y, v.z + z);};
            // -
            vec3 operator-(const vec3& v) const {return vec3(x - v.x,y - v.y, z- v.z);};
            // *
            vec3 operator*(const T& scalar) const {return vec3(x*scalar, y*scalar, z*scalar);};
            // /
            vec3 operator/(const T& scalar) const {
                if (std::abs(scalar) < static_cast<T>(1e-9) || scalar == static_cast<T>(0)) {
                    throw std::runtime_error("Division by zero is not allowed.");
                }
                return vec3(x/scalar, y/scalar, z/scalar);};
            // dot
            T dot(const vec3& v) const {return x*v.x + y*v.y + z*v.z;};
            // cross
            vec3 cross(const vec3& v) const {
                T c1 = y*v.z - z*v.y;
                T c2 = z*v.x - x*v.z;
                T c3 = x*v.y - y*v.x;
                return vec3(c1,c2,c3);                 
            };
            bool approx(const vec3& v) const {
                return udfuncs::approx_equal(x, v.x) &&
                        udfuncs::approx_equal(y, v.y) &&
                        udfuncs::approx_equal(z, v.z);  
            };
            T magnitude() const {
                return std::sqrt(x*x + y*y + z*z);
            };

            std::string toString() const {
                return std::to_string(x)+ " " + std::to_string(y)+ " " + std::to_string(z);
            } 

    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const vec3<T>& obj) {
            os << obj.x << ' ' << obj.y << ' ' << obj.z;
        return os;
    };
    template<typename T, typename U>
    vec3<T> operator*(U&& scalar, vec3<T>& v) {
        return vec3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
    };


    // strings, for fun :L
    template <>
    class vec3<std::string> {
        public:
            std::string x,y,z;
            vec3() : x(""), y(""), z("") {};
            vec3(const std::string& x_set, const std::string& y_set, const std::string& z_set) : x(x_set), y(y_set), z(z_set) {};

            //operator overlaod
            // +
            vec3<std::string> operator+(const vec3<std::string>& v) const {
                return vec3<std::string>(v.x + " + " + x, v.y + " + " + y, v.z + " + " + z);
            };
            // -
            vec3<std::string> operator-(const vec3<std::string>& v) const {
                return vec3<std::string>(v.x + " - " + x, v.y + " - " + y, v.z + " - " + z);
            };
            vec3<std::string> operator*(const std::string& v) const {
                return vec3<std::string>(x + " * " + v, y + " * " + v, z + " * " + v);
            };
    };

}




#endif // VEC3_HF