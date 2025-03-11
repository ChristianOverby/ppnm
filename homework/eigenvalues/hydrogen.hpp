#ifndef HYDROGEN_HF
#define HYDROGEN_HF

#include "../includes/matrix.hpp"

namespace pp {

    struct hydrogenSchrodinger {
        int pointCount;
        double rmax, dr;
        pp::matrix H;
        pp::vector r;

        hydrogenSchrodinger(double rmax, double dr);
        
        void solve();
        void convergenceDeltaR();
        static void convergenceDeltaRparallel(double dr_p);
        void convergenceDeltaRmax();
        static void convergenceDeltaRmaxparallel(double drmax_p);
        void hamiltonian();
    };

}





#endif //HYDROGEN_HF
