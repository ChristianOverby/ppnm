#ifndef HYDROGEN_HF
#define HYDROGEN_HF

#include "../includes/matrix.hpp"
#include "../includes/vector.hpp"

namespace ppnm {

    struct hydrogenSchrodinger {
        int pointCount;
        double rmax, dr;
        ppnm::matrix<double> H;
        ppnm::vector<double> r;

        hydrogenSchrodinger(double rmax, double dr);
        
        void solve();
        void wavefunctions();
        void convergence();
        void hamiltonian();
    };

}





#endif //HYDROGEN_HF
