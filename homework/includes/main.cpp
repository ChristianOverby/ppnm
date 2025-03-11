#include "matrix.hpp"
#include "vmatrix.hpp"
#include <iostream> 

int main() 
{
    pp::matrix A(2,2);
    pp::matrix B(20, 20);
    pp::vector M(3);
    M[0] = 1.0;
    M[1] = 2.0;
    M[2] = 3.0;
    // copy assignment of A to B
    B = A;
    std::cout << "B = A = \n" << B << std::endl;

    // copy constructor of C from A
    pp::matrix C(A);
    std::cout << "copy constructor of C from A " << "\n" << "C = A = \n" << C << std::endl;

    // move constructor of D from A without std::move
    pp::matrix D(std::move(A));
    std::cout << "move constructor of D from A " << "\n" << "D = A = \n" << D << std::endl;    

    std::cout << "A = \n" << A << std::endl;

    B[0, 0] = 1;
    std::cout << "B(0,0) = 1 = \n" << B << std::endl;

    B[0,1] = 2;
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
    std::cout << "E(1,0) = 2 = \n" << E << std::endl;
    E.set(1,1,5);
    std::cout << "E.set(1,1,5) = \n" << E << std::endl;


    ppnm::vmatrix<double> G = F-E;
    std::cout << "G = F - E = \n" << G << std::endl;

    // timing of creating 1e5 matrices with random values¨
    double start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        pp::matrix H(2,2);
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

    std::cout << "Time taken to create 1e5 vmatrices and push_back them: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // timing of creating 2 1e5 matrices with random values and adding them
    start = clock();
    for(size_t i = 0; i < 1e5; i++)
    {
        pp::matrix H(2,2);
        pp::matrix I(2,2);
        for (size_t j = 0; j < 4; j++)
        {
            H(j/2, j%2) = rand() % 100;
            I(j/2, j%2) = rand() % 100;
        }
        pp::matrix J = H+I;
        if (i == 1e5-1) std::cout << "J = \n" << J << std::endl;
    }
    end = clock();

    std::cout << "Time taken to create 1e5 matrices and push_back them: " << (end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    std::cout << "using vmatrix is slower so i will not implement any more to this class" << std::endl; 

    B = pp::matrix::identity(B.size1());

    std::cout << "Convert B to identity matrix = \n" << B << std::endl;

    B = pp::matrix(10,10);
    B(9,0) = 1;
    B = pp::matrix::identity(B.size1());

    std::cout << "Convert B to 10x10 matrix and then to to identity matrix = \n" << B << std::endl;

    B.setDiagonal(9);

    std::cout << "Set the main diagonal of B to 9 \n" << B << std::endl;

    B.setDiagonal(0); B.setDiagonal(1, 1);

    std::cout << "Set the +1 offset diagonal of B to 1 \n" << B << std::endl;

    pp::matrix mat(3, 3);   // Create a 3x3 matrix
    mat.set(0, 0, 1);
    mat.set(1, 1, 2);
    mat.set(0, 2, 3);

    std::cout << "create and fill 3x3 matrix\n" << mat;

    std::cout << "Is matrix upper trianular? " << (mat.upperTriangular() ? "Yes" : "No") << std::endl;
    std::cout << "Is matrix lower trianular? " << (mat.lowerTriangular() ? "Yes" : "No") << "\n" << std::endl;

    pp::matrix transposed = mat.transpose();  // Transpose the matrix

    std::cout << "Transpose said matrix \n" << transposed;

    std::cout << "Is transposed matrix upper trianular? " << (transposed.upperTriangular() ? "Yes" : "No") << std::endl;
    std::cout << "Is transposed matrix lower trianular? " << (transposed.lowerTriangular() ? "Yes" : "No") << "\n" << std::endl;

    std::cout << "transposed matrix and M vector: \nmatrix = \n" << transposed << "\nM = \n" << M << std::endl;

    transposed[2] = (M);

    std::cout << "transposed matrix has vector M inserted at col 3: \n" << transposed << std::endl;

    transposed[1] = M;
    transposed[0] = M;

    std::cout << "transposed matrix has vector M inserted at all col: \n" << transposed << std::endl;

    return 0;
}
