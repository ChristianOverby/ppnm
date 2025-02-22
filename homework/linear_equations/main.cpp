#include <iostream>
#include <cstdlib>
#include "../includes/matrix.hpp"
#include "../includes/vmatrix.hpp"
#include "../includes/vector.hpp"
#include "QRGS.hpp"

int main() 
{   
    // Simple tests i did to make sure stuff works.
    ppnm::matrix<double> testMatrix(4,4);
    testMatrix = testMatrix.identity();
    ppnm::vmatrix<double> testVmatrix(4,4);
    testVmatrix.set(3,3,12);
    ppnm::vector<double> testVector;
    testVector.add(1);
    testVector.add(2);
    testVector.add(3);
    testVector.add(4);
    std::cout << "Test of Matrix, Vmatrix and vector class: \n" << testMatrix << "\n\n" << testVmatrix << "\n\n" << testVector << std::endl; 
    int q = std::rand() % 100;
    std::cout << "Random number: " << q << std::endl;
    // fill testMatrix with random numbers
    srand(1);
    for (size_t i = 0; i < testMatrix.getRows(); ++i) {
        for (size_t j = 0; j < testMatrix.getCols(); ++j) {
            testMatrix.set(i, j, std::rand() % 100);
        }
    }

    std::cout << "print matrix \n" << testMatrix << std::endl;

    ppnm::QRGS test(testMatrix);
    
    test.printMatrices();

    ppnm::vector<double> solveTest = test.solve(testVector);
    
    std::cout << "Solve the testMatrix*x = testVector:  \n" << solveTest << std::endl;

    // Example matrix (2x3)
    ppnm::matrix<double> mat(2, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

    // Example vector (3x1)
    ppnm::vector<double> vec;
    vec.add(1);
    vec.add(2);
    vec.add(3);


    return 0;
}