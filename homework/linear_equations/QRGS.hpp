#ifndef QRGS_HF
#define QRGS_HF

#include "../includes/matrix.hpp"

namespace pp {
  struct QRGS {
  pp::matrix A, Q, R;
  // A matrix for storing the Input matrix

  // fyi should proably use a vectorconstructed matrix for this. However i stopped devloping mine since it was
  // a couple of milliseconds slower...
  // constructor performs stabilized Gram-Schmidt orthogonalization of an n×m (where n≥m) matrix A calculating R & Q.
  QRGS(const pp::matrix& M);

  // solving Ax = b   by back-substitution due to
  //         Rx = Q^T*b  with Q^T * b = y
  pp::vector solve(pp::vector b);

  NUMBER det();
  pp::matrix inverse();
  pp::matrix inverse2();
  pp::matrix getQ() const {return Q;}
  pp::matrix getR() const {return R;}

  // print the three matrices
  void printMatrices();
};

} // namespace ppnm

#endif // QRGS_HF
