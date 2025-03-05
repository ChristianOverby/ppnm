#include <iostream>
#include "EVD.hpp"
#include "../includes/matrix.hpp"
#include "hydrogen.hpp"

// made this functions since there is a large build up of rounding errors.
bool approx_low_tol(const ppnm::matrix<double>& mat, const ppnm::matrix<double>& mat2)
            {
                if (mat.getRows() != mat2.getRows() || mat.getCols() != mat2.getCols())
                    return false;
            for (size_t i = 0; i < mat2.getRows(); ++i) {
                for (size_t j = 0; j < mat2.getCols(); ++j) {
                    if (!ppnm::approx(mat(i, j), mat2(i,j), 1e-6)) {
                        return false;
                    }
                }
            }
            return true;
            }


int main() {

    std::cout << "testing" << std::endl;

    size_t n = 5; // Matrix size
    ppnm::matrix<double> B(n, n);

    B = B.randomizedSymetricMatrix(0, 100);

    ppnm::matrix<double> A = B; // Symmetric matrix

    // Compute Eigenvalue Decomposition
    ppnm::EVD evd(A);

    // Extract eigenvectors (V) and eigenvalues (w)
    ppnm::matrix<double> V = evd.V;
    ppnm::vector<double> w = evd.w;

    // Construct diagonal matrix D
    ppnm::matrix<double> D(n, n);
    for (size_t i = 0; i < n; i++)
        D(i, i) = w[i];

    // Compute V^T * A * V
    ppnm::matrix<double> VTAV = V.transpose() * A * V;

    // Compute V * D * V^T
    ppnm::matrix<double> VDVT = V * D * V.transpose();

    // Compute V^T * V and V * V^T
    ppnm::matrix<double> VTV = V.transpose() * V;
    ppnm::matrix<double> VVT = V * V.transpose();

    std::cout << "The vector w and the matrix V in the EVD class\nw: \n" << evd.w << "\nV: \n" << evd.V << std::endl;

    std::cout << "random matrix A =\n" << A << std::endl;

    // Check if VTAV ≈ D
    std::cout << "The matrix V^T A V =\n" << VTAV << std::endl;
    // Approximate all indices of the matrix with 0 and set it to 0 if true
    for (size_t i = 0; i < VTAV.getCols(); ++i) {
        for (size_t j = 0; j < VTAV.getCols(); ++j) {
            if (ppnm::approx(VTAV(i, j), 0.0, 1e-6)) {
                VTAV.set(i, j, 0);
            if (ppnm::approx(VTAV(i, j), 1.0, 1e-6)) {
                VTAV.set(i, j, 1);
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
    std::cout << "Check V^T V ≈ I: " << (approx_low_tol(VTV, VTV.identity()) ? "PASS" : "FAIL") << std::endl;

    // Check if V V^T ≈ I
    std::cout << "Check V V^T ≈ I: " << (approx_low_tol(VVT, VVT.identity()) ? "PASS" : "FAIL") << std::endl;

    ppnm::hydrogenSchrodinger hydrogenTest(7,0.5);

    std::cout << hydrogenTest.dr << std::endl;

    hydrogenTest.hamiltonian();



}