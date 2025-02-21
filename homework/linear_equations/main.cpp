#include <iostream>
#include <cstdlib>
#include "../includes/matrix.hpp"
#include "../includes/vmatrix.hpp"
#include "../includes/vector.hpp"

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
    
    return 0;
}