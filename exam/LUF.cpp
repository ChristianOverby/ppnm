#include "LUF.hpp"
#include <cassert>
#include <iostream>

namespace pp {
        LUF::LUF(const pp::matrix& A) : L(A.size1(), A.size2()), U(A.size1(), A.size2()), P(A.size1())
    {
        int n = A.size1();
        A_C = A; // Copy of A since it'll now be modifed

        //Pivoting
        for (int i = 0; i < n; ++i) {P[i] = i;} // Initialize permutation matrix to identity matrix
        for (int i = 0; i<n; i++) {
            int p_i = i;
            double max = std::abs(A_C[i,i]); // max value in copy of A
            for (int k = i+1; k< n; k++) {
                if(std::abs(A_C[k,i]) >max) {
                    max = std::abs(A_C[k,i]);
                    p_i = k;
                }
            }

            // Swap rows i larger value was found
            if (p_i != i) {
                std::swap(P[i], P[p_i]);
                for (int j = 0; j<n; j++) {
                    std::swap(A_C[i,j], A_C[p_i,j]);
                    if(j<i) {std::swap(L[i,j], L[p_i,j]);}
                }
            }
            // now the LU composition can be done
            L[i,i] = 1;
            for(int j = i; j< n; j++) {
                double LUsum = 0;
                for (int k = 0; k<i; k++) {
                    LUsum += L[i,k]*U[k,j];
                }   
                U[i,j] = A_C[i,j] - LUsum;
            }
            
            for(int j = i+1; j < n; j++) {
                double LUsum = 0;
                for (int k = 0; k<i; k++) {
                    LUsum += L[j,k]*U[k,i];
                }
                L[j,i] = 1/U[i,i]*(A_C[j,i] - LUsum);

            }
        }
        
    }
    
    pp::vector LUF::solve(const pp::vector& b)
    {
        // A*x = b         =>        LU*x = b
        // L*y = b    ,    U*x = y

        // Foward substituion L*y = b Since lower triangular
        int n = b.size();
        pp::vector b_perm(n);
        for (int i = 0; i < n; ++i){
            b_perm[i] = b[P[i]]; } // Apply permutation
        pp::vector x(n), y(n);
        for (int i = 0; i< n; i++ ) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i,j]*y[j];
            }
            y[i] = (b_perm[i]-sum);
        }

        // Backwards subsitution U*x = y since upper triangular
        for (int i = n-1; i>=0; i-- ) {
            double sum = 0;
            for (int j = i+1; j<n; j++) {
                sum += U[i,j] *x[j];
            }
            x[i] = (y[i]-sum) / U[i,i];
        }

        return x;
    }
    
    double LUF::det()
    {
        assert(U.size1() == U.size2() && "Must be square matrix to determine determinant");
        NUMBER sum = 0.0;
        sum++;
        for (int i = 0; i < std::min(U.size1(), U.size2()); i++) {
            std::cout << U(i, i) << std::endl;
            sum *= U(i, i);
        }
        return sum;
    }
    
    pp::matrix LUF::inverse()
    {
        //assert(Q.size2() == Q.size1() && "Only solves for square matrices"); // should be square
        size_t n = U.size2();
        pp::matrix M_inv(n, n);

        // Solve R * x_i = e_i for each column i
        for (size_t i = 0; i < n; i++) {
            pp::vector e(n); // Identity vector
            e[i] = 1; // Set the i-th entry to 1

            // Solve for x_i using back-substitution (which is implemented in solve)
            pp::vector x = solve(e);

            // Store the computed inverse column in M_inv
            M_inv[i]= x;
        }

        return M_inv;
    }
    
    pp::matrix LUF::getL()
    {
        return L;
    }
    
    pp::matrix LUF::getU()
    {
        return U;
    }
    
    pp::matrix LUF::getApivoted()
    {
        return A_C;
    }
    

}