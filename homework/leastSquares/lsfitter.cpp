#include "lsfitter.hpp"
#include "../linear_equations/QRGS.hpp"
#include <iostream>

namespace pp {
    std::pair<pp::vector, pp::matrix> ode_ls_fit(
        const std::vector<std::function<double(double)>>& fs, 
        const vector& x, 
        const vector& y, 
        const vector& dy) 
        // Need to construct A and b then solve for c. A*c = b
    {    
        // Construct A and b
        int n = x.size();
        int m = fs.size();
        pp::matrix A(n,m); 
        pp::vector b(n);  

        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
                A[i, k] = fs[k](x[i]) / dy[i]; // design matrix
            }
            b[i] = y[i] / dy[i]; // weighted measurement vector 
        }
        pp::QRGS qrgs(A);
        pp::vector c = qrgs.solve(b);
        // with QR-decomp Σ = (A^T A)^−1 = (R^T R)^−1 = R^−1(R^−1)T.
        pp::matrix invA = qrgs.inverse(); // returns the inverse of the QR-decomposed matrix.
        pp::matrix pcov = invA * invA.transpose();

        std::pair<pp::vector, pp::matrix> bar(c,pcov);
        return bar;

    }
}
