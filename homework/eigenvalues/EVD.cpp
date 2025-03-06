#include "EVD.hpp"
#include <cmath>

namespace ppnm {

    EVD::EVD(const ppnm::matrix<double>& M) : w(M.getCols()), V(M.identity())
    {
        ppnm::matrix<double> A = M;

        // Apply Jacobi rotations using the cyclic method
        ppnm::vector<ppnm::matrix<double>> AV_vec = cyclic(A);
        
        // Extract the diagonalized matrix and eigenvector matrix
        A = AV_vec[0]; // The transformed matrix (should be diagonal)
        V = AV_vec[1]; // The eigenvector matrix

        // Copy diagonal elements into the w vector (these are the eigenvalues)
        for (size_t i = 0; i < A.getCols(); i++) {
            w[i] = A(i, i);
        }
        }
    
    void EVD::timesJ(ppnm::matrix<double>& A, int p, int q, double theta)
    {
        double c=std::cos(theta),s=std::sin(theta);
        for(size_t i=0;i < A.getCols();i++){
            double aip=A(i,p),aiq=A(i,q);
            A(i,p)=c*aip-s*aiq;
            A(i,q)=s*aip+c*aiq;
            }
    }
    
    void EVD::Jtimes(ppnm::matrix<double>& A, int p, int q, double theta)
    {
        double c=std::cos(theta),s=std::sin(theta);
        for(size_t j=0;j<A.getCols();j++){
            double apj=A(p,j),aqj=A(q,j);
            A(p,j)= c*apj+s*aqj;
            A(q,j)=-s*apj+c*aqj;
            }
    }
    
    ppnm::vector<ppnm::matrix<double>> EVD::cyclic(ppnm::matrix<double>& A)
    {
        size_t n = A.getCols();
        bool changed;
        do{
            changed=false;
            for(size_t p = 0 ; p < n-1 ; p++)
            for(size_t q = p+1 ; q<n ; q++){
                double apq = A(p,q), app=A(p,p), aqq=A(q,q);
                double theta = 0.5*std::atan2(2*apq,aqq-app);
                double c = std::cos(theta), s = std::sin(theta);
                double new_app=c*c*app-2*s*c*apq+s*s*aqq;
                double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
                if(new_app!=app || new_aqq!=aqq) // do rotation
                    {
                    changed=true;
                    timesJ(A,p,q, theta); // A←A*J 
                    Jtimes(A,p,q,-theta); // A←JT*A 
                    timesJ(V,p,q, theta); // V←V*J
                    }
            }
        }while(changed);
        
        ppnm::vector<ppnm::matrix<double>> AV_vec(2);
        AV_vec[0] = A;
        AV_vec[1] = V;
        
        return AV_vec;
    }

    std::ostream& operator<<(std::ostream& os, const EVD& obj) {
            os << "w = \n" << obj.w << "\nV =\n" << obj.V << std::endl;
        return os;
    }


}