#ifndef QRGS_HF
#define QRGS_HF

#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"
#include "../includes/functions.hpp"
#include <iostream>

namespace ppnm {
template <typename T> struct QRGS {
  ppnm::matrix<T> A, Q, R;
  // A matrix for storing the Input matrix

  // fyi should proably use a vectorconstructed matrix for this. However i stopped devloping mine since it was
  // a couple of milliseconds slower...
  // constructor performs stabilized Gram-Schmidt orthogonalization of an n×m (where n≥m) matrix A calculating R & Q.
  QRGS(const ppnm::matrix<T>& M) : A(M), Q(M), R(M.getCols(), M.getCols()) {
    size_t m = M.getCols();
    for (size_t i = 0; i < m; i++) {
      R(i, i) = Q[i].magnitude();
      if (ppnm::approx(R(i, i), T())) { throw std::runtime_error("Matrix is rank-deficient (division by zero)");} // Check for zero magnitude (linear dependence)
      Q.setCol(i, Q[i] / R(i, i)); // Normalize i'th input matrix coloumn and put in Q
      for (size_t j = i + 1; j < m; j++) {     // subtract this projection from the rest of A coloumns
        R(i, j) = Q[i].dot(Q[j]);
        Q.setCol(j, Q[j] - Q[i] * R(i, j));
      }
    }
  }

  // solving Ax = b   by back-substitution due to
  //         Rx = Q^T*b  with Q^T * b = y
  ppnm::vector<T> solve(ppnm::vector<T> b) {
    // y = Q^T * b
    ppnm::vector<T> y = Q.transpose()*b;
    ppnm::vector<T> x(y.size);
    //std::cout << x << std::endl;
    size_t i = y.size; // size of vector, e.g. 3
    size_t m = y.size; // numver of cols, e.g. 3
    while (i-- > 0)
    {
      T sum = 0;
      for (size_t j = i+1; j < m; j++) // doesnt run for e.g i = 3 
      {
        sum += R(i,j)*x[j]; // summming over the coloumn that we are in.
      }
      x[i] = (y[i] - sum)/R(i,i);
    }
    return x;
  }

  T det() {
    assert(R.getCols() == R.getRows() && "Must be square matrix to determine determinant");
    T sum = T();
    sum++;
    for(size_t i = 0; i< std::min(R.getRows(), R.getCols()); i++) {
      std::cout << R(i,i) << std::endl;
        sum *= R(i,i);
    }
    return sum;
  }
  // this method uses the solve function wich requires an additional Q mulitplatication. (Could also modify solve
  // but this would make that method unintuitive)
  ppnm::matrix<T> inverse() {
    // M = QR
    // M^-1 = R^-1 * Q^-1
    // M^-1 = R^-1 * Q^T (since Q is orthogonal)
    assert(Q.getRows() == Q.getCols() && "Only solves for square matrices"); // should be square
    size_t n = Q.getCols();
    ppnm::matrix<T> M_inv(n, n);

    // Solve R * x_i = e_i for each column i
    for (size_t i = 0; i < n; i++) {
        ppnm::vector<T> e(n); // Identity vector
        e[i] = 1; // Set the i-th entry to 1

        // Solve for x_i using back-substitution (which is implemented in solve)
        ppnm::vector<T> x = solve(Q*e);

        // Store the computed inverse column in M_inv
        M_inv.setCol(i, x);
    }

    return M_inv * Q.transpose();
}

  ppnm::matrix<T> inverse2(){
    // M = QR
    // M^-1 = R^-1*Q^-1
    // M^-1 = R^-1*Q^T (since Q orthongoal)
    assert(Q.getRows() == Q.getCols() && "Only solves for square matricies"); // should be square
    size_t n = Q.getCols();

    ppnm::matrix<T> R_inv(n, n);
    ppnm::matrix<T> M_inv(n, n);

    // solving R^-1 - This is really much the same as what happens during the decomposition.
    // Since R is upper tiangular it is easy to solve for R^-1 using back substitution
    // R^-1 * x_i = e_i 
    for (size_t i = 0; i<n; i++) // each coloumn is looped over
    {
      ppnm::vector<T> e(n); // the identity vector 
      e[i] = 1; // inititalize the e vector to be the actual identity vector
      ppnm::vector<T> x(n); // vector to hold the solution
      for (size_t j = n; j-- > 0;) // Now solving for R * x = e     Starts at the last row e.g. j = n-1 
      {
        T sum = T();
        for (size_t k = j + 1; k<n; k++) // this then loops forward summing all the terms the the rgiht of the diagonal in the j row that we are in
        // e.g runs over all the alreadu known values of x
        {
          sum += R(j,k) *x[k];
        }
        x[j] = (e[j]-sum)/R(j,j);
      }
      R_inv.setCol(i, x);
    }
     
    ppnm::matrix<T> Q_T = Q.transpose(); // stored in it's own variable for clairty

    M_inv = R_inv * Q_T;

    return M_inv;

  }


  ppnm::matrix<T> getQ() const {
    return Q;
  }
  ppnm::matrix<T> getR() const {
    return R;
  }

  // print the three matrices
  void printMatrices() {
    std::cout << "Q matrix: \n" << Q << "\n" << std::endl;
    std::cout << "A matrix: \n" << A << "\n" << std::endl;
    std::cout << "R matrix: \n" << R << "\n" << std::endl;
  }

};

} // namespace ppnm

#endif // QRGS_HF
