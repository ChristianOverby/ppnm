#include "EVD.hpp"
#include "../includes/matrix.hpp"
#include <cmath>
#include<iostream>

namespace pp {

    EVD::EVD(const pp::matrix& M) : w(M.size2())
    {
        V = pp::matrix::identity(M.size2());
        pp::matrix A = M;

        // Apply Jacobi rotations using the cyclic method
        std::pair<pp::matrix, pp::matrix> AV_vec = cyclic(A);
        
        // Extract the diagonalized matrix and eigenvector matrix
        A = AV_vec.first; // The transformed matrix (should be diagonal)
        V = AV_vec.second; // The eigenvector matrix

        // Copy diagonal elements into the w vector (these are the eigenvalues)
        for (int i = 0; i < A.size2(); i++) {
            w.data[i] = A[i, i];
        }
        }
    
    void EVD::timesJ(pp::matrix& A, int p, int q, double theta)
    {
        double c=std::cos(theta),s=std::sin(theta);
        for(int i=0;i < A.size2();i++){
            double aip=A(i,p),aiq=A(i,q);
            A[i,p]=c*aip-s*aiq;
            A[i,q]=s*aip+c*aiq;
            }
    }
    
    void EVD::Jtimes(pp::matrix& A, int p, int q, double theta)
    {
        double c=std::cos(theta),s=std::sin(theta);
        for(int j=0;j<A.size2();j++){
            double apj=A(p,j),aqj=A(q,j);
            A(p,j)= c*apj+s*aqj;
            A(q,j)=-s*apj+c*aqj;
            }
    }
    
    std::pair<pp::matrix, pp::matrix> EVD::cyclic(pp::matrix& A)
    {
        int n = A.size2();
        bool changed;
        do{
            changed=false;
            for(int p = 0 ; p < n-1 ; p++)
            for(int q = p+1 ; q<n ; q++){
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
        
        std::pair<pp::matrix, pp::matrix> AV_vec;
        AV_vec.first = A;
        AV_vec.second = V;
        
        return AV_vec;
    }

    std::ostream& operator<<(std::ostream& os, const EVD& obj) {
            os << "w = \n" << obj.w << "\nV =\n" << obj.V << std::endl;
        return os;
    }


}