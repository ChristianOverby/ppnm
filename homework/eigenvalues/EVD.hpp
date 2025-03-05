#ifndef EVD_HF
#define EVD_HF

#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"

namespace ppnm {
    class EVD{
    public:
    ppnm::vector<double> w; // Eigenvectors
    ppnm::matrix<double> V; // Eigenvalues

    EVD(const ppnm::matrix<double>& M);

    static void timesJ(ppnm::matrix<double>& A, int p, int q, double theta);
    static void Jtimes(ppnm::matrix<double>& A, int p, int q, double theta);

    ppnm::vector<ppnm::matrix<double>> cyclic(ppnm::matrix<double>& A);

    };

    std::ostream& operator<<(std::ostream& os, const EVD& obj);
}


#endif // EVD_HF