#ifndef QRGS_HF
#define QRGS_HF

#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"

namespace ppnm {
template <typename T> struct QRGS {
  ppnm::matrix<T> A, Q, R;

  QRGS(ppnm::matrix<T> M) : A(), Q(), R() {}

  ppnm::vector<T> decomp();

  void solve();

  void det();
};

} // namespace ppnm

#endif // QRGS_HF
