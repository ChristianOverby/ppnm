#include <iostream>
#include "tests.hpp"
#include "QRGS.hpp"
#include <string>
#include <regex>
#include "../includes/matrix.hpp"

int main(int argc, char* arg[]) 
{ 
    // note that doing it this way is a terrible idea. Should just define what should be run
    // Also using the bash time util is not optimal due to different reasons. e.g you cannot run different things
    // at the same time also the precision is only to millisecond...
    // would definitely use chronos next time and just write the data to a filestream.
    std::string str;
    std::string input;
    for (int i = 1; i < argc; i++) {
        str = arg[i];
        if(str == "--runUnitTest" || str == "-rut") {
            std::cout << "\nDoing one testQRGSdecomp verbose test:" << std::endl;
            pp::testQRGSdecomp(1, true);
            std::cout << "\nTesting QR decomp on 2000 0-20 x 0-20 matricies" << std::endl;
            pp::testQRGSdecomp(2000);
            
            std::cout << "\nDoing one testQRGSsolve verbose test:" << std::endl;
            pp::testQRGSsolve(1, true);
            std::cout << "\nTesting solve on 2000 0-20 x 0-20 matricies and 0-20 vector" << std::endl;
            pp::testQRGSsolve(2000);

            std::cout << "\nDoing one testQRGSinverse verbose test:" << std::endl;
            pp::testQRGSinverse(1, true);
            std::cout << "\nTesting inverse on 2000 0-20 x 0-20 matricies" << std::endl;
            pp::testQRGSsolve(2000);
        }
        if(str == "--sizeSquare" || str == "-ssq") {
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

    

    // ppnm::matrix<double> matrix(300,300); matrix = matrix.randomizedMatrix(0, 100);
    // ppnm::QRGS<double> matrixQRdecomposed(matrix);
    return 0;
}