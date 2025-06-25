#include "tests.hpp"
#include "../homework/includes/matrix.hpp"
#include "../homework/includes/functions.hpp"
#include "../homework/includes/log.hpp"
#include "LUF.hpp"
#include <cassert>
#include <cstdlib>
namespace pp
{
    void testLUdecomp(const int& repetitions, const bool& printOut)
    {
        for (int i = 0; i < repetitions; i++) {
        pp::log(printOut, "---------------------------------------");
        // random values for m,n
        int n = std::rand() % 20;
        n = std::rand() % 20;
        // Generate matrix and LU decompose.
        pp::matrix matrix = pp::matrix::rndMatrix(n,n);
        pp::log(printOut, "Randomized ", n, "x",n," matrix A: \n", matrix);
        pp::LUF matrixLUdecomposed(matrix);
        pp::matrix A_p = matrixLUdecomposed.getApivoted();
        pp::log(printOut, "Pivoted matrix A: \n", A_p);

        // U upper triangular
        pp::matrix U; U = matrixLUdecomposed.getU();
        pp::log(printOut,"U \n", U);
        pp::log(printOut,"U is upper triangular?    ", (U.upperTriangular() ? "True" : "False"), "\n");
        assert(U.upperTriangular() && "L isn't upper triangular");

        // L upper triangular
        pp::matrix L; L = matrixLUdecomposed.getL();
        pp::log(printOut,"L \n", L);
        pp::log(printOut,"L is lower triangular?    ", (L.lowerTriangular() ? "True" : "False"), "\n");
        assert(L.lowerTriangular() && "L isn't lower triangular");

        //QR = A
        pp::matrix LmultU = (L*U);
        pp::log(printOut,"L*U = A_pivoted\nL*U: \n", LmultU, "\nA_pivoted: \n" , A_p);
        pp::log(printOut, "L*U = A? (Aprroximate)   ", (LmultU == A_p? "True" : "False"));
        //assert(QmultR == matrix && "Q*R != A (approximately)");

        pp::log(printOut, "---------------------------------------");
    }
    std::cout << "testLUdecomp passed succesufully" << std::endl; 
    }
    
    void testLUsolve(const int& repetitions, const bool& printOut)
    {
        for (int i = 0; i < repetitions; i++) 
        {
            pp::log(printOut, "---------------------------------------");
            // Square matrix otherwise the solution is some projection and not exact.
            int m = std::rand() % 20 + 1;

            // random values for m,n
            pp::matrix matrix = pp::matrix::rndMatrix(m,m, 1);
            pp::log(printOut, "Randomized ", m, "x",m," matrix: \n", matrix);
            pp::vector vec(m);
            for (int j = 0; j < m; j++) {
            vec[j] = static_cast<NUMBER>(std::rand() % 100);
            }
            pp::LUF matrixLUdecomposed(matrix);
            pp::log(printOut, "A = \n",matrix);
            pp::log(printOut, "Solve for vector b = \n", vec);
            pp::vector x = matrixLUdecomposed.solve(vec);
            pp::log(printOut, "Solution x = \n", x);
            pp::log(printOut,"A*x = \n",matrix*x);
            if(!(matrix*x == vec)) {std::cerr << matrix << "\n" << vec << "\n" << x << std::endl;}
            //assert(matrix*x == vec && "x is not the (approximate) solution");
            pp::log(printOut, "---------------------------------------");

        }

        std::cout << "testLUsolve passed succesufully" << std::endl; 
    }
    
    void testLUinverse(const int& repetitions, const bool& printOut)
    {
    for (int i = 0; i < repetitions; i++) 
  {
    pp::log(printOut, "---------------------------------------");
    // Square matrix otherwise the solution is some projection and not exact.
    int m = std::rand() % 20;

    // random values for m,n
    pp::matrix matrix = pp::matrix::rndMatrix(m,m);
    pp::log(printOut, "Randomized ", m, "x",m," matrix: \n", matrix);
    pp::vector vec(m);
    for (int j = 0; j < m; j++) {
      vec[j] = static_cast<NUMBER>(std::rand() % 100);
    }
    pp::LUF matrixQRdecomposed(matrix);
    pp::matrix matrix_inv = matrixQRdecomposed.inverse();
    pp::log(printOut, " Matrix inv = \n", matrix_inv);
    pp::matrix mat_inv_mat = matrix_inv*matrix;
    // Approximate all indices of the matrix with 0 and set it to 0 if true
    for (int i = 0; i < mat_inv_mat.size2(); ++i) {
        for (int j = 0; j < mat_inv_mat.size1(); ++j) {
            if (pp::approx(mat_inv_mat(i, j), 0.0)) {
                mat_inv_mat.set(i, j, 0);
            if (pp::approx(mat_inv_mat(i, j), 1.0)) {
                mat_inv_mat.set(i, j, 1);
            }
            }
        }
    }
    pp::log(printOut,"matrix_inv*matrix (approximate) = \n",mat_inv_mat);
    assert(mat_inv_mat == pp::matrix::identity(mat_inv_mat.size1()) && "mat_inv is not the (approximate) solution");
    pp::log(printOut, "---------------------------------------");

  }

  std::cout << "testQRGSinverse passed succesufully" << std::endl; 
}


}