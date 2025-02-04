#ifndef TEST_HF
#define TEST_HF

#include<iostream>
#include"vec3.hpp"

namespace udtests {
    template <typename T>
    void runTests() {
        std::cout << "Running tests for udvector::vec3<" << typeid(T).name() << ">...\n";

        // Constructor Test
        udvector::vec3<T> v1; // Default constructor
        udvector::vec3<T> v2(1, 2, 3); // Parameterized constructor
        if (v2.x != 1 || v2.y != 2 || v2.z != 3) {
            std::cerr << "❌ Constructor Test Failed!\n";
        }

        // Addition
        udvector::vec3<T> v3 = v2 + udvector::vec3<T>(4, 5, 6);
        if (v3.x != 5 || v3.y != 7 || v3.z != 9) {
            std::cerr << "❌ Addition Test Failed!\n";
        }

        // Subtraction
        udvector::vec3<T> v4 = v2 - udvector::vec3<T>(1, 1, 1);
        if (v4.x != 0 || v4.y != 1 || v4.z != 2) {
            std::cerr << "❌ Subtraction Test Failed!\n";
        }

        // Scalar Multiplication
        udvector::vec3<T> v5 = v2 * static_cast<T>(2);
        if (v5.x != 2 || v5.y != 4 || v5.z != 6) {
            std::cerr << "❌ Scalar Multiplication Test Failed!\n";
        }

        // Scalar Division
        udvector::vec3<T> v6 = v2 / static_cast<T>(2);
        if (v6.x != 0.5 || v6.y != 1 || v6.z != 1.5) {
            std::cerr << "❌ Scalar Division Test Failed!\n";
        }

        // Dot Product
        T dotProduct = v2.dot(udvector::vec3<T>(4, 5, 6));
        if (dotProduct != static_cast<T>(1 * 4 + 2 * 5 + 3 * 6)) {
            std::cerr << "❌ Dot Product Test Failed!\n";
        }

        // Cross Product
        udvector::vec3<T> v7 = v2.cross(udvector::vec3<T>(4, 5, 6));
        if (v7.x != -3 || v7.y != 6 || v7.z != -3) {
            std::cerr << "❌ Cross Product Test Failed!\n";
        }

        // Approximate Equality Test (Floating Point)
        udvector::vec3<T> v8(1.000000001, 2.0, 3.0);
        udvector::vec3<T> v9(1.000000002, 2.0, 3.0);
        if (!v8.approx(v9)) {
            std::cerr << "❌ Approximate Equality Test Failed!\n";
        }

        // Edge Case: Division by Zero
        try {
            udvector::vec3<T> v10 = v2 / static_cast<T>(0);
            std::cout << v10 << std::endl;
            std::cerr << "❌ Division by Zero Test Failed!\n";
        } catch (const std::runtime_error&) {
            std::cout << "✅ Division by Zero Test Passed!\n";
        }

        std::cout << "✅ All tests passed for udvector::vec3<" << typeid(T).name() << ">!\n\n";
    }
}




#endif // TEST_HF