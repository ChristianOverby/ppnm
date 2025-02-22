#ifndef QRGS_HF
#define QRGS_HF

#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"
#include "../includes/functions.hpp"
#include <iostream>

namespace ppnm {
template <typename T> struct QRGS {
  ppnm::matrix<T> Q, A, R;
  // A matrix for storing the Input matrix

  // fyi should proably use a vectorconstructed matrix for this. However i stopped devloping mine since it was
  // a couple of miliseconds slower...
  // constructor performs stabilized Gram-Schmidt orthogonalization of an n×m (where n≥m) matrix A calculating R & Q.
  QRGS(ppnm::matrix<T> M) : Q(M.getRows(), M.getCols()), A(M), R(M.getRows(), M.getCols()) 
  {
    size_t m = M.getCols();
    for (size_t i = 0; i < m; i++)
    {
      R(i,i) = A.getCol(i).magnitude();

      // Check for zero magnitude (linear dependence)
      if (ppnm::approx(R(i,i), T())) 
        {
            throw std::runtime_error("Matrix is rank-deficient (division by zero)");
        }

      // Normalize i'th input matrix coloumn and put in Q 
      Q.setCol(i, A.getCol(i)/R(i,i));

      // subtract this projection from the rest of A coloumns
      for (size_t j = i+1; j < m; j++) 
      {
        R(i,j) = Q.getCol(i).dot(A.getCol(j));
        ppnm::vector tempvec = A.getCol(j)-Q.getCol(i)*R(i,j);
        A.setCol(j, tempvec);
      }

    }
  }

  // solving Ax = b   by back-substitution due to
  //         Rx = Q^T*b  with Q^T * b = y
  ppnm::vector<T> solve(ppnm::vector<T> b) {
    // y = Q^T * b
    ppnm::vector<T> y = Q.transpose()*b;
    ppnm::vector<T> x(y.getSize());
    //std::cout << x << std::endl;
    size_t i = y.getSize(); // size of vector, e.g. 3
    size_t m = y.getSize(); // numver of cols, e.g. 3
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

  double det();

  ppnm::matrix<T> inverse();

  // print the three matrices
  void printMatrices() {
    std::cout << "Q matrix: \n" << Q << "\n" << std::endl;
    std::cout << "A matrix: \n" << A << "\n" << std::endl;
    std::cout << "R matrix: \n" << R << "\n" << std::endl;
  }

};

} // namespace ppnm

#endif // QRGS_HF
