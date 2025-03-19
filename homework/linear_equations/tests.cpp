#include "tests.hpp"
#include "../includes/matrix.hpp"
#include "../includes/functions.hpp"
#include "../includes/log.hpp"
#include "QRGS.hpp"
#include <cassert>
#include <cstdlib>

namespace pp {

void testQRGSdecomp(const int& repetitions, const bool& printOut){
  
  for (int i = 0; i < repetitions; i++) {
    pp::log(printOut, "---------------------------------------");
    // random values for m,n
    int a = std::rand() % 20;
    int b = std::rand() % 20;

    // Assign the larger value to n and the smaller to m
    int n = std::max(a, b);
    int m = std::min(a, b);

    // Generate matrix and QR decompose.
    pp::matrix matrix = pp::matrix::rndMatrix(n,m);
    pp::log(printOut, "Randomized ", n, "x",m," matrix: \n", matrix);
    pp::QRGS matrixQRdecomposed(matrix);
    pp::matrix Q = matrixQRdecomposed.getQ();

    // Q^T * Q
    pp::matrix QTQ = Q.transpose() * Q;

    pp::log(printOut,"Q^T * Q \n",QTQ);
    // Approximate all indices of the matrix with 0 or 1 and set it to 0 or 1 if true
    for (int i = 0; i < QTQ.size1(); ++i) {
        for (int j = 0; j < QTQ.size2(); ++j) {
            if (pp::approx(QTQ[i, j], 0.0)) {
                QTQ[i, j] = 0.0;
            }
            if (pp::approx(QTQ[i, j], 1.0)) {
                QTQ[i, j] = 1.0;
            }
        }
    }
    pp::log(printOut,"Q^T * Q (Aprroximate 0) \n",QTQ);
    assert(QTQ == pp::matrix::identity(QTQ.size2()) && "Q^T * Q != I");
    // R upper triangular
    pp::matrix R; R = matrixQRdecomposed.getR();
    pp::log(printOut,"R \n", R);
    pp::log(printOut,"R is upper triangular?    ", (R.upperTriangular() ? "True" : "False"), "\n");
    assert(R.upperTriangular() && "R isn't upper triangular");

    //QR = A
    pp::matrix QmultR = Q*R;
    pp::log(printOut,"Q*R = Q\nQ*R: \n", QmultR, "\nA: \n" , matrix);
    pp::log(printOut, "Q*R = A? (Aprroximate)   ", (QmultR == matrix ? "True" : "False"));
    //assert(QmultR == matrix && "Q*R != A (approximately)");


    pp::log(printOut, "---------------------------------------");
  }
  std::cout << "testQRGSsolve passed succesufully" << std::endl; 
}

void testQRGSsolve(const int& repetitions, const bool& printOut) {
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
    pp::QRGS matrixQRdecomposed(matrix);
    pp::log(printOut, "R = \n",matrixQRdecomposed.getR());
    pp::log(printOut, "Solve for vector b = \n", vec);
    pp::vector x = matrixQRdecomposed.solve(vec);
    pp::log(printOut, "Solution x = \n", x);
    pp::log(printOut,"A*x = \n",matrix*x);
    assert(matrix*x == vec && "x is not the (approximate) solution");
    pp::log(printOut, "---------------------------------------");

  }

  std::cout << "testQRGSsolve passed succesufully" << std::endl; 
}


void testQRGSinverse(const int &repetitions, const bool& printOut) {
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
    pp::QRGS matrixQRdecomposed(matrix);
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

void testOnRealMatrix(const pp::matrix& mat)
{
  pp::QRGS matrixQRdecomposed(mat);
    pp::matrix Q = matrixQRdecomposed.getQ();

    // Q^T * Q
    pp::matrix QTQ = Q.transpose() * Q;

    pp::log(true,"Q^T * Q \n",QTQ);
    // Approximate all indices of the matrix with 0 or 1 and set it to 0 or 1 if true
    for (int i = 0; i < QTQ.size1(); ++i) {
        for (int j = 0; j < QTQ.size2(); ++j) {
            if (pp::approx(QTQ[i, j], 0.0)) {
                QTQ[i, j] = 0.0;
            }
            if (pp::approx(QTQ[i, j], 1.0)) {
                QTQ[i, j] = 1.0;
            }
        }
    }
    pp::log(true,"Q^T * Q (Aprroximate 0) \n",QTQ);
    assert(QTQ == pp::matrix::identity(QTQ.size2()) && "Q^T * Q != I");
    // R upper triangular
    pp::matrix R; R = matrixQRdecomposed.getR();
    pp::log(true,"R \n", R);
    pp::log(true,"R is upper triangular?    ", (R.upperTriangular() ? "True" : "False"), "\n");
    assert(R.upperTriangular() && "R isn't upper triangular");

    //QR = A
    pp::matrix QmultR = Q*R;
    pp::log(true,"Q*R = Q\nQ*R: \n", QmultR, "\nA: \n" , mat);
    pp::log(true, "Q*R = A? (Aprroximate)   ", (QmultR == mat ? "True" : "False"));
    //assert(QmultR == matrix && "Q*R != A (approximately)");


    pp::log(true, "---------------------------------------");
}



} // namespace pp