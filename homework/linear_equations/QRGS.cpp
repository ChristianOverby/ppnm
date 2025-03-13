#include "QRGS.hpp"
#include <iostream>
#include "../includes/functions.hpp"
#include "../includes/matrix.hpp"
#include <cassert>

namespace pp {


    QRGS::QRGS(const pp::matrix& M) : A(M), Q(M), R(M.size2(), M.size2()) {
    size_t m = M.size2();
    for (size_t i = 0; i < m; i++) {
      R(i, i) = Q[i].norm();
      if (pp::approx(R(i, i), 0.0)) { throw std::runtime_error("Matrix is rank-deficient (division by zero)");} // Check for zero magnitude (linear dependence)
      Q[i] = Q[i] / R(i, i); // Normalize i'th input matrix coloumn and put in Q7
      for (size_t j = i + 1; j < m; j++) {     // subtract this projection from the rest of A coloumns
        R(i, j) = Q[i].dot(Q[j]);
        Q[j] = Q[j] - Q[i] * R(i, j);
      }
    }
  }

    // solving Ax = b   by back-substitution due to
    //         Rx = Q^T*b  with Q^T * b = y
    pp::vector QRGS::solve(pp::vector b) 
    {
        // y = Q^T * b
        pp::vector y = Q.transpose()*b;
        pp::vector x(y.size());
        //std::cout << x << std::endl;
        size_t i = y.size(); // size of vector, e.g. 3
        size_t m = y.size(); // numver of cols, e.g. 3
        while (i-- > 0)
        {
        NUMBER sum = 0;
        for (size_t j = i+1; j < m; j++) // doesnt run for e.g i = 3 
        {
            sum += R(i,j)*x[j]; // summming over the coloumn that we are in.
        }
        x[i] = (y[i] - sum)/R(i,i);
        }
        return x;
    }

    NUMBER QRGS::det() {
      assert(R.size1() == R.size2() &&
             "Must be square matrix to determine determinant");
      NUMBER sum = 0.0;
      sum++;
      for (int i = 0; i < std::min(R.size1(), R.size2()); i++) {
        std::cout << R(i, i) << std::endl;
        sum *= R(i, i);
      }
      return sum;
    }

  pp::matrix QRGS::inverse() {
    // M = QR
    // M^-1 = R^-1 * Q^-1
    // M^-1 = R^-1 * Q^T (since Q is orthogonal)
    //assert(Q.size2() == Q.size1() && "Only solves for square matrices"); // should be square
    size_t n = Q.size2();
    pp::matrix M_inv(n, n);

    // Solve R * x_i = e_i for each column i
    for (size_t i = 0; i < n; i++) {
        pp::vector e(n); // Identity vector
        e[i] = 1; // Set the i-th entry to 1

        // Solve for x_i using back-substitution (which is implemented in solve)
        pp::vector x = solve(e);

        // Store the computed inverse column in M_inv
        M_inv[i]= x;
    }

    return M_inv;
}

  void QRGS::printMatrices() {
    std::cout << "Matrix A:\n" << A << std::endl;
    std::cout << "Matrix Q:\n" << Q << std::endl;
    std::cout << "Matrix R:\n" << R << std::endl;
  }
}


