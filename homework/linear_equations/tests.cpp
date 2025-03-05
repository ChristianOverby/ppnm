#include "tests.hpp"
#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"
#include "../includes/log.hpp"
#include "QRGS.hpp"
#include <cstdlib>

namespace ppnm {

void testQRGSdecomp(const int& repetitions, const bool& printOut){
  
  for (int i = 0; i < repetitions; i++) {
    ppnm::log(printOut, "---------------------------------------");
    // random values for m,n
    int a = std::rand() % 20;
    int b = std::rand() % 20;

    // Assign the larger value to n and the smaller to m
    int n = std::max(a, b);
    int m = std::min(a, b);

    // Generate matrix and QR decompose.
    ppnm::matrix<double> matrix(n,m); matrix = matrix.randomizedMatrix(0.0, 100.0);
    ppnm::log(printOut, "Randomized ", n, "x",m," matrix: \n", matrix);
    ppnm::QRGS<double> matrixQRdecomposed(matrix);
    ppnm::matrix<double> Q = matrixQRdecomposed.getQ();

    // Q^T * Q
    ppnm::matrix<double> QTQ = Q.transpose() * Q;

    // Approximate all indices of the matrix with 0 or 1 and set it to 0 or 1 if true
    for (size_t i = 0; i < QTQ.getRows(); ++i) {
        for (size_t j = 0; j < QTQ.getCols(); ++j) {
            if (ppnm::approx(QTQ(i, j), 0.0)) {
                QTQ.set(i, j, 0);
            if (ppnm::approx(QTQ(i, j), 1.0)) {
                QTQ.set(i, j, 1);
            }
            }
        }
    }
    ppnm::log(printOut,"Q^T * Q (Aprroximate 0) \n",QTQ);
    assert(QTQ == QTQ.identity() && "Q^T * Q != I");
    // R upper triangular
    ppnm::matrix<double> R; R = matrixQRdecomposed.getR();
    ppnm::log(printOut,"R \n", R);
    ppnm::log(printOut,"R is upper triangular?    ", (R.upperTriangular() ? "True" : "False"), "\n");
    assert(R.upperTriangular() && "R isn't upper triangular");

    //QR = A
    ppnm::matrix<double> QmultR = Q*R;
    ppnm::log(printOut,"Q*R = Q\nQ*R: \n", QmultR, "\nA: \n" , matrix);
    ppnm::log(printOut, "Q*R = A? (Aprroximate)   ", (QmultR == matrix ? "True" : "False"));
    assert(QmultR == matrix && "Q*R != A (approximately)");


    ppnm::log(printOut, "---------------------------------------");
  }
  std::cout << "testQRGSsolve passed succesufully" << std::endl; 
}

void testQRGSsolve(const int& repetitions, const bool& printOut) {
  for (int i = 0; i < repetitions; i++) 
  {
    ppnm::log(printOut, "---------------------------------------");
    // Square matrix otherwise the solution is some projection and not exact.
    int m = std::rand() % 20;

    // random values for m,n
    ppnm::matrix<double> matrix(m,m); matrix = matrix.randomizedMatrix(0, 100);
    ppnm::log(printOut, "Randomized ", m, "x",m," matrix: \n", matrix);
    ppnm::vector<double> vec(m);
    for (int j = 0; j < m; j++) {
      vec[j] = static_cast<double>(std::rand() % 100);
    }
    ppnm::QRGS<double> matrixQRdecomposed(matrix);
    ppnm::log(printOut, "R = \n",matrixQRdecomposed.getR());
    ppnm::log(printOut, "Solve for vector b = \n", vec);
    ppnm::vector<double> x = matrixQRdecomposed.solve(vec);
    ppnm::log(printOut, "Solution x = \n", x);
    ppnm::log(printOut,"A*x = \n",matrix*x);
    assert(matrix*x == vec && "x is not the (approximate) solution");
    ppnm::log(printOut, "---------------------------------------");

  }

  std::cout << "testQRGSsolve passed succesufully" << std::endl; 
}


void testQRGSinverse(const int &repetitions, const bool& printOut) {
  for (int i = 0; i < repetitions; i++) 
  {
    ppnm::log(printOut, "---------------------------------------");
    // Square matrix otherwise the solution is some projection and not exact.
    int m = std::rand() % 20;

    // random values for m,n
    ppnm::matrix<double> matrix(m,m); matrix = matrix.randomizedMatrix(0, 100);
    ppnm::log(printOut, "Randomized ", m, "x",m," matrix: \n", matrix);
    ppnm::vector<double> vec(m);
    for (int j = 0; j < m; j++) {
      vec[j] = static_cast<double>(std::rand() % 100);
    }
    ppnm::QRGS<double> matrixQRdecomposed(matrix);
    ppnm::matrix<double> matrix_inv = matrixQRdecomposed.inverse();
    ppnm::log(printOut, " Matrix inv = \n", matrix_inv);
    ppnm::matrix<double> mat_inv_mat = matrix_inv*matrix;
    // Approximate all indices of the matrix with 0 and set it to 0 if true
    for (size_t i = 0; i < mat_inv_mat.getRows(); ++i) {
        for (size_t j = 0; j < mat_inv_mat.getCols(); ++j) {
            if (ppnm::approx(mat_inv_mat(i, j), 0.0)) {
                mat_inv_mat.set(i, j, 0);
            if (ppnm::approx(mat_inv_mat(i, j), 1.0)) {
                mat_inv_mat.set(i, j, 1);
            }
            }
        }
    }
    ppnm::log(printOut,"matrix_inv*matrix (approximate) = \n",mat_inv_mat);
    assert(mat_inv_mat == matrix.identity() && "mat_inv is not the (approximate) solution");
    ppnm::log(printOut, "---------------------------------------");

  }

  std::cout << "testQRGSinverse passed succesufully" << std::endl; 
}


} // namespace ppnm