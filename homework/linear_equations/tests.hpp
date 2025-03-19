#ifndef TESTS_HF
#define TESTS_HF

#include "../includes/matrix.hpp"

namespace pp {

    void testQRGSdecomp(const int& repetitions, const bool& printOut = false);

    void testQRGSsolve(const int& repetitions, const bool& printOut = false);

    void testQRGSinverse(const int& repetitions, const bool& printOut = false);

    void testOperationsCount(const int& repetitions, const bool& printOut = false);

    void testOnRealMatrix(const pp::matrix& mat);
}




#endif // TESTS_HF