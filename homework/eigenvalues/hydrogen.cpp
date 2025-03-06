#include "hydrogen.hpp"
#include "EVD.hpp"

namespace ppnm
{

    // initializes the hamiltonian matrix and the radial coordinate vector r 
    hydrogenSchrodinger::hydrogenSchrodinger(double rmax, double dr) : rmax(rmax), dr(dr)
    {
        pointCount = static_cast<int>(rmax/dr) -1;
        r = ppnm::vector<double>(pointCount);
        H = ppnm::matrix<double>(pointCount, pointCount);

        for (int i = 0; i < pointCount; i++) {
            r[i] = dr * (i + 1);
        }
    }

    // Constrtuct the hamiltonian matrix
    void hydrogenSchrodinger::hamiltonian()
    {
        // kinetic nergy frontfactor
        double kf = -0.5 / (dr*dr);
        //Construct kinetic energy matrix
        H.setDiagonal((-2*kf),0); H.setDiagonal(kf*1,1); H.setDiagonal(kf*1,-1);
        for(int i = 0; i < pointCount; i++) {
            H(i,i) = H(i,i) - 1/r[i];
        }
        std::cout << H << std::endl;
    }

    void hydrogenSchrodinger::solve()
    {
        ppnm::EVD evd(H);
        ppnm::vector<double> egValues = evd.w;
        ppnm::matrix<double> egVectors = evd.V;
    }
    
    void hydrogenSchrodinger::wavefunctions()
    {
        
    }
    
    void hydrogenSchrodinger::convergence()
    {
        
    }
}