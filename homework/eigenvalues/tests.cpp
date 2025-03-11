#include "tests.hpp"
#include "../includes/functions.hpp"
#include <iostream>
#include "EVD.hpp"



namespace pp
{
    // made this functions since there is a large build up of rounding errors.
    bool approx_low_tol(const pp::matrix& mat, const pp::matrix& mat2)
    {
            {
                if (mat.size1() != mat2.size1() || mat.size2() != mat2.size2())
                    return false;
            for (int i = 0; i < mat2.size1(); ++i) {
                for (int j = 0; j < mat2.size2(); ++j) {
                    if (!pp::approx(mat[i, j], mat2[i,j], 1e-6)) {
                        return false;
                    }
                }
            }
            return true;
            }
    }


    

    void test1()
    {
    std::cout << "Testing" << std::endl;
    size_t n = 5; // Matrix size
    pp::matrix A = pp::matrix::rndSymMatrix(n,n);
    std::cout << "Matrix A:\n" << A << std::endl;
    // Compute Eigenvalue Decomposition
    pp::EVD evd(A);

    // Extract eigenvectors (V) and eigenvalues (w)
    pp::matrix V = evd.V;
    pp::vector w = evd.w;

    // Construct diagonal matrix D
    pp::matrix D(n, n);
    for (size_t i = 0; i < n; i++)
        D(i, i) = w[i];

    // Compute V^T * A * V
    pp::matrix VTAV = V.transpose() * A * V;

    // Compute V * D * V^T
    pp::matrix VDVT = V * D * V.transpose();

    // Compute V^T * V and V * V^T
    pp::matrix VTV = V.transpose() * V;
    pp::matrix VVT = V * V.transpose();

    std::cout << "The vector w and the matrix V in the EVD class\nw: \n" << evd.w << "\nV: \n" << evd.V << std::endl;

    std::cout << "random matrix A =\n" << A << std::endl;

    // Check if VTAV ≈ D
    std::cout << "The matrix V^T A V =\n" << VTAV << std::endl;
    // Approximate all indices of the matrix with 0 and set it to 0 if true
    for (int i = 0; i < VTAV.size2(); ++i) {
        for (int j = 0; j < VTAV.size2(); ++j) {
            if (pp::approx(VTAV[i, j], 0.0, 1e-6)) {
                VTAV[i, j] = 0;
            if (pp::approx(VTAV[i, j], 1.0, 1e-6)) {
                VTAV[i, j] = 1;
            }
            }
        }
    }
    std::cout << "The approximated 0 matrix V^T A V =\n" << VTAV << std::endl;

    std::cout << "the matrix D =\n" << D << std::endl;
    std::cout << "\nCheck V^T A V ≈ D: " << (approx_low_tol(VTAV,D) ? "PASS" : "FAIL") << std::endl;
    // Check if VDVT ≈ A
    std::cout << "Check V D V^T ≈ A: " << (approx_low_tol(VDVT, A) ? "PASS" : "FAIL") << std::endl;

    // Check if V^T V ≈ I
    std::cout << "Check V^T V ≈ I: " << (approx_low_tol(VTV, pp::matrix::identity(VTV.size2())) ? "PASS" : "FAIL") << std::endl;

    // Check if V V^T ≈ I
    std::cout << "Check V V^T ≈ I: " << (approx_low_tol(VVT, pp::matrix::identity(VVT.size2())) ? "PASS" : "FAIL") << std::endl;
    }
}