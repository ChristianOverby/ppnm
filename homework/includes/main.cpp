#include "matrix.hpp"
#include "vmatrix.hpp"
#include "vector.hpp"
#include <iostream> 

int main() 
{
    ppnm::matrix<double> A(2,2);
    ppnm::matrix<double> B(20, 20);
    ppnm::vector<double> M;
    M.add(1.0);
    M.add(2.0);
    M.add(3.0);
    std::cout << "M = \n" << M << std::endl;
    M.remove(2);
    std::cout << "M = \n" << M << std::endl;
    std::cout << "A = \n" << A << std::endl;
    std::cout << "B = \n" << B << std::endl;
    // copy assignment of A to B
    B = A;
    std::cout << "B = A = \n" << B << std::endl;

    // copy constructor of C from A
    ppnm::matrix<double> C(A);
    std::cout << "copy constructor of C from A " << "\n" << "C = A = \n" << C << std::endl;

    // move constructor of D from A without std::move
    ppnm::matrix<double> D(std::move(A));
    std::cout << "move constructor of D from A " << "\n" << "D = A = \n" << D << std::endl;    

    std::cout << "A = \n" << A << std::endl;

    // delete vector A
    A.~matrix();
    std::cout << "A deleted" << std::endl;

    B(0, 0) = 1;
    std::cout << "B(0,0) = 1 = \n" << B << std::endl;

    B.set(0,1,2);
    std::cout << "B.set(0,1,2) = \n" << B << std::endl;
    // iterate over 

    // resize
    // B.resize(4,4);
    // std::cout << "B.resize(4,4) = \n" << B << std::endl; 
    C = B+B;
    std::cout << "C = B + B = \n" << C << std::endl;
    C = C-B;
    std::cout << "C = C - B = \n" << C << std::endl;
    C = C*2;
    std::cout << "C = B*2 = \n" << C << std::endl;

    ppnm::vmatrix<double> E(2,2);
    ppnm::vmatrix<double> F(20, 20);
    std::cout << "E = \n" << E << std::endl;
    std::cout << "F = \n" << F << std::endl;
    // copy assignment of E to F
    F = E;
    std::cout << "F = E = \n" << F << std::endl;
    E(1,0) = 2;
    E.set(1,1,5);
    std::cout << "E(1,0) = 2 = \n" << E << std::endl;
    std::cout << "E.set(1,1,5) = \n" << E << std::endl;


    ppnm::vmatrix<double> G = F-E;
    std::cout << "G = F - E = \n" << G << std::endl;

    // timing of creating 1e5 matrices with random values¨
    double start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        ppnm::matrix<double> H(2,2);
        for (size_t j = 0; j < 4; j++)
        {
            H(j/2, j%2) = rand() % 100;
        }
        if (i == 1e5-1) std::cout << "H = \n" << H << std::endl;
    }
    double end = clock();
    std::cout << "Time taken to create 1e5 matrices: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // timing of creating 1e5 vmatrices with random values
    start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        ppnm::vmatrix<double> H(2,2);
        for (size_t j = 0; j < 4; j++)
        {
            H(j/2, j%2) = rand() % 100;
        }
        if (i == 1e5-1) std::cout << "H = \n" << H << std::endl;
    }
    end = clock();
    std::cout << "Time taken to create 1e5 vmatrices: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // timing of creating 2 1e5 vmatrices with random values and adding them
    start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        ppnm::vmatrix<double> H(2,2);
        ppnm::vmatrix<double> I(2,2);
        for (size_t j = 0; j < 4; j++)
        {
            H(j/2, j%2) = rand() % 100;
            I(j/2, j%2) = rand() % 100;
        }
        ppnm::vmatrix<double> J = H+I;
        if (i == 1e5-1) std::cout << "J = \n" << J << std::endl;
    }
    end = clock();

    std::cout << "Time taken to create 1e5 vmatrices and add them: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // timing of creating 2 1e5 matrices with random values and adding them
    start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        ppnm::matrix<double> H(2,2);
        ppnm::matrix<double> I(2,2);
        for (size_t j = 0; j < 4; j++)
        {
            H(j/2, j%2) = rand() % 100;
            I(j/2, j%2) = rand() % 100;
        }
        ppnm::matrix<double> J = H+I;
        if (i == 1e5-1) std::cout << "J = \n" << J << std::endl;
    }
    end = clock();

    std::cout << "Time taken to create 1e5 matrices and add them: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    std::cout << "using vmatrix is slower so i will not implement any more to this class" << std::endl; 

    B.identity();

    std::cout << "Convert B to identity matrix = \n" << B << std::endl;

    B = ppnm::matrix<double>(10,10);
    B(9,0) = 1;
    B = B.identity();

    std::cout << "Convert B to 10x10 matrix and then to to identity matrix = \n" << B << std::endl;

    B.setDiagonal(9);

    std::cout << "Set the main diagonal of B to 9 \n" << B << std::endl;

    B.setDiagonal(0); B.setDiagonal(1, 1);

    std::cout << "Set the +1 offset diagonal of B to 1 \n" << B << std::endl;

    ppnm::matrix<int> mat(3, 3);   // Create a 3x3 matrix
    mat.set(0, 0, 1);
    mat.set(1, 1, 2);
    mat.set(0, 2, 3);

    std::cout << "create and fill 3x3 matrix\n" << mat;

    std::cout << "Is matrix upper trianular? " << (mat.upperTriangular() ? "Yes" : "No") << std::endl;
    std::cout << "Is matrix lower trianular? " << (mat.lowerTriangular() ? "Yes" : "No") << "\n" << std::endl;

    ppnm::matrix<int> transposed = mat.transpose();  // Transpose the matrix

    std::cout << "Transpose said matrix \n" << transposed;

    std::cout << "Is transposed matrix upper trianular? " << (transposed.upperTriangular() ? "Yes" : "No") << std::endl;
    std::cout << "Is transposed matrix lower trianular? " << (transposed.lowerTriangular() ? "Yes" : "No") << "\n" << std::endl;

    return 0;
}
