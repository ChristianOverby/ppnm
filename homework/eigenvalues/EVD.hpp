#ifndef EVD_HF
#define EVD_HF

#include "../includes/matrix.hpp"
#include <utility>

namespace pp {
    class EVD{
    public:
    pp::vector w; // Eigenvectors
    pp::matrix V; // Eigenvalues

    EVD(const pp::matrix& M);

    void timesJ(pp::matrix& A, int p, int q, double theta);
    void Jtimes(pp::matrix& A, int p, int q, double theta);

    std::pair<pp::matrix, pp::matrix> cyclic(pp::matrix& A);

    };

    std::ostream& operator<<(std::ostream& os, const EVD& obj);
}


#endif // EVD_HF