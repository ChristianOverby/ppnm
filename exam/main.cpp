#include <iostream>
#include "../homework/includes/matrix.hpp"
#include "LUF.hpp"
#include "../homework/linear_equations/QRGS.hpp"
#include <string>
#include <regex>
#include "tests.hpp"

int main(int argc, char* arg[]) {

    std::string str;
    std::string input;
    for (int i = 1; i < argc; i++) {
        str = arg[i];
        if(str == "--runUnitTest" || str == "-rut") {
            std::cout << "---------------------------------------" << std::endl;
            std::cout << "Pivoting LU decomposition testing the implemented functions:" << std::endl;
            std::cout << "---------------------------------------\n" << std::endl;
            std::cout << "\nDoing one testLUdecomp verbose test:" << std::endl;
            pp::testLUdecomp(1, true);
            
            std::cout << "\nDoing one testLUsolve verbose test:" << std::endl;
            pp::testLUsolve(1, true);

            std::cout << "\nDoing one testLUinverse verbose test:" << std::endl;
            pp::testLUinverse(1, true);
            std::cout << "---------------------------------------" << std::endl;
            std::cout << "Time count for QR-decomposition can be seen in plot.benchmark.svg" << std::endl;
            std::cout << "QR decomp is approximately 2 times slower" << std::endl;

            
        }
    
        if(str == "--sizeSquareLU" || str == "-ssqLU") {
            // no error checking for more numbers. Only checks the first two inpiuts
             if (i+1 < argc) {
                input = arg[i+1];
                std::stringstream nStream(input);
                std::string matchOutput;
                std::regex numberPattern(R"(^-?\d+$)"); // Matches integers
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                int m = std::stod(matchOutput);
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                int rep = std::stod(matchOutput);
                for (int i=0 ; i < rep; i++){
                    pp::matrix matrix = pp::matrix::rndMatrix(m,m);
                    pp::LUF matrixQRdecomposed(matrix);
                    }
                }
        }

        if(str == "--sizeSquareQR" || str == "-ssqQR") {
            // no error checking for more numbers. Only checks the first two inpiuts
             if (i+1 < argc) {
                input = arg[i+1];
                std::stringstream nStream(input);
                std::string matchOutput;
                std::regex numberPattern(R"(^-?\d+$)"); // Matches integers
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                int m = std::stod(matchOutput);
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                int rep = std::stod(matchOutput);
                for (int i=0 ; i < rep; i++){
                    pp::matrix matrix = pp::matrix::rndMatrix(m,m);
                    pp::QRGS matrixQRdecomposed(matrix);
                    }
                }
        }
        
    }


    

}