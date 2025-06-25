#ifndef TESTS_HF
#define TESTS_HF

#include "../homework/includes/matrix.hpp"

namespace pp {

    void testLUdecomp(const int& repetitions, const bool& printOut = false);

    void testLUsolve(const int& repetitions, const bool& printOut = false);

    void testLUinverse(const int& repetitions, const bool& printOut = false);

    void testOperationsCount(const int& repetitions, const bool& printOut = false);

    void testOnRealMatrix(const pp::matrix& mat);
}




#endif // TESTS_HF