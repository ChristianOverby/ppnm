#include <iostream>
#include <string>
#include "includes/vec3.hpp"
#include "includes/tests.hpp"

int main() {


    //float tests
    std::cout << "--------------------------" << std::endl;
    std::cout << "double tests" << std::endl;
    udvector::vec3<double> v1_d = udvector::vec3<double>();
    udvector::vec3<double> v2_d = udvector::vec3<double>(1.1,2.2,3.3);
    udvector::vec3<double> v3_d = udvector::vec3<double>(4.4,5.5,6.6);
    std::cout << "v1: " << v1_d << std::endl;
    std::cout << "v2: " << v2_d << std::endl;
    std::cout << "v3: " << v3_d << std::endl;

    std::cout << "v2 + v3 " << std::endl;
    udvector::vec3<double> v4_d = v2_d + v3_d;
    std::cout << v4_d << std::endl;
    v4_d.x = 2;
    std::cout << "v2 - v3 " << std::endl;
    udvector::vec3<double> v5_d = v2_d - v3_d;
    std::cout << v5_d << std::endl;

    std::cout << "v2 * 5 " << std::endl;
    udvector::vec3<double> v6_d = v2_d * 5;
    std::cout << v6_d << std::endl;

    std::cout << "5 * v2 " << std::endl;
    udvector::vec3<double> v7_d = 5 * v2_d;
    std::cout << v7_d << std::endl;

    std::cout << "v2 / 5 " << std::endl;
    udvector::vec3<double> v8_d = v2_d / 5;
    std::cout << v8_d << std::endl;

    std::cout << "v2 * v3 " << std::endl;
    double v9_d = v2_d.dot(v3_d);
    std::cout << v9_d << std::endl;

    std::cout << "v2 x v3 " << std::endl;
    udvector::vec3<double> v10_d = v2_d.cross(v3_d);
    std::cout << v10_d << std::endl;

    std::cout << "v2 approx_equal v3 " << std::endl;
    bool v11_d = v2_d.approx(v3_d);
    std::cout << (v11_d ? "true" : "false") << std::endl;

    std::cout << "|v2|" << std::endl;
    double v12_d = v2_d.magnitude();
    std::cout << v12_d << std::endl;

    std::cout << "v2 toString" << std::endl;
    std::string v13_d = v2_d.toString();
    std::cout << v13_d << std::endl;
    std::cout << "--------------------------" << std::endl;


    //double tests
    std::cout << "float tests" << std::endl;
    udvector::vec3<float> v1_f = udvector::vec3<float>();
    udvector::vec3<float> v2_f = udvector::vec3<float>(1.1,2.2,3.3);
    udvector::vec3<float> v3_f = udvector::vec3<float>(4.4,5.5,6.6);
    std::cout << "v1: " << v1_f << std::endl;
    std::cout << "v2: " << v2_f << std::endl;
    std::cout << "v3: " << v3_f << std::endl;

    std::cout << "v2 + v3 " << std::endl;
    udvector::vec3<float> v4_f = v2_f + v3_f;
    std::cout << v4_f << std::endl;

    std::cout << "v2 - v3 " << std::endl;
    udvector::vec3<float> v5_f = v2_f - v3_f;
    std::cout << v5_f << std::endl;

    std::cout << "v2 * 5 " << std::endl;
    udvector::vec3<float> v6_f = v2_f * 5;
    std::cout << v6_f << std::endl;

    std::cout << "v2 / 5 " << std::endl;
    udvector::vec3<float> v7_f = v2_f / 5;
    std::cout << v7_f << std::endl;

    std::cout << "v2 * v3 " << std::endl;
    float v9_f = v2_f.dot(v3_f);
    std::cout << v9_f << std::endl;

    std::cout << "v2 x v3 " << std::endl;
    udvector::vec3<float> v10_f = v2_f.cross(v3_f);
    std::cout << v10_f << std::endl;

    std::cout << "v2 approx_equal v3 " << std::endl;
    bool v11_f = v2_f.approx(v3_f);
    std::cout << (v11_f ? "true" : "false") << std::endl;

    std::cout << "|v2|" << std::endl;
    float v12_f = v2_f.magnitude();
    std::cout << v12_f << std::endl;

    std::cout << "--------------------------" << std::endl;

    // int tests
    std::cout << "integer tests" << std::endl;
    udvector::vec3<int> v1_i = udvector::vec3<int>();
    udvector::vec3<int> v2_i = udvector::vec3<int>(1,2,3);
    udvector::vec3<int> v3_i = udvector::vec3<int>(4,5,6);
    std::cout << "v1: " << v1_i << std::endl;
    std::cout << "v2: " << v2_i << std::endl;
    std::cout << "v3: " << v3_i << std::endl;

    std::cout << "v2 + v3 " << std::endl;
    udvector::vec3<int> v4_i = v2_i + v3_i;
    std::cout << v4_i << std::endl;

    std::cout << "v2 - v3 " << std::endl;
    udvector::vec3<int> v5_i = v2_i - v3_i;
    std::cout << v5_i << std::endl;

    std::cout << "v2 * 5 " << std::endl;
    udvector::vec3<int> v6_i = v2_i * 5;
    std::cout << v6_i << std::endl;

    std::cout << "v2 / 5 " << std::endl;
    udvector::vec3<int> v7_i = v2_i / 5;
    std::cout << v7_i << std::endl;

    std::cout << "v2 * v3 " << std::endl;
    int v9_i = v2_i.dot(v3_i);
    std::cout << v9_i << std::endl;

    std::cout << "v2 x v3 " << std::endl;
    udvector::vec3<int> v10_i = v2_i.cross(v3_i);
    std::cout << v10_i << std::endl;

    std::cout << "v2 approx_equal v3 " << std::endl;
    bool v11_i = v2_i.approx(v3_i);
    std::cout << (v11_i ? "true" : "false") << std::endl;

    std::cout << "|v2|" << std::endl;
    int v12_i = v2_i.magnitude();
    std::cout << v12_i << std::endl;

    std::cout << "--------------------------" << std::endl;

    // string tests
    std::cout << "String tests" << std::endl;
    udvector::vec3<std::string> v1_s = udvector::vec3<std::string>();
    udvector::vec3<std::string> v2_s = udvector::vec3<std::string>("1", "2", "3");
    udvector::vec3<std::string> v3_s = udvector::vec3<std::string>("4", "5", "6");
    std::cout << "v1: " << v1_s << std::endl;
    std::cout << "v2: " << v2_s << std::endl;
    std::cout << "v3: " << v3_s << std::endl;

    std::cout << "v2 + v3 " << std::endl;
    udvector::vec3<std::string> v4_s = v2_s + v3_s;
    std::cout << v4_s << std::endl;

    std::cout << "v2 - v3 " << std::endl;
    udvector::vec3<std::string> v5_s = v2_s - v3_s;
    std::cout << v5_s << std::endl;

    std::cout << "v2 * 5 " << std::endl;
    udvector::vec3<std::string> v6_s = v2_s * "5";
    std::cout << v6_s << std::endl;

    std::cout << "--------------------------" << std::endl;

    //Extensive testing
    udtests::runTests<float>();  // Test with float
    udtests::runTests<double>(); // Test with double
    udtests::runTests<long double>(); // Test with long double
    //udtests::runTests<int>();    // Test with int (integer operations) Since i've not implemneted integer conversion during divison this test will fail.

    return 0;
}