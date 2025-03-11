#include "tests.hpp"
#include "hydrogen.hpp"
#include <string>
#include <regex>
#include <iostream>
#include "../includes/functions.hpp"

int main(int argc, char* arg[]) {

    std::string str;
    std::string input;
    for (int i = 1; i < argc; i++) {

    str = arg[i];
        if(str == "--runUnitTest" || str == "-rut") {
            pp::test1();    
        }
        if(str == "--hydrogenSolve" || str == "-hs") {
            if (i+1 < argc) {
                input = arg[i+1];
                std::stringstream nStream(input);
                std::string matchOutput;
                std::regex numberPattern(R"(^-?\d+(\.\d+)?$)"); // Matches integers and doubles
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                double rmax = std::stod(matchOutput);
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                double dr = std::stod(matchOutput);
            pp::hydrogenSchrodinger hydrogenTest(rmax,dr);

            hydrogenTest.hamiltonian();

            hydrogenTest.solve();
            
            std::cout << "Running convergence for Δr on one thread" << std::endl;
            double drTime = pp::timeit([&]() { return hydrogenTest.convergenceDeltaR(); });
            std::cout << "Time taken: " << drTime / 1000000 << " seconds" << std::endl;

            std::cout << "Running convergence for rmax on one thread" << std::endl;
            double gg = pp::timeit([&]() { return hydrogenTest.convergenceDeltaRmax(); });
            std::cout << "Time taken: " << gg / 1000000 << " seconds" << std::endl;
            }
        }
        if(str == "--divergenceDeltaR" || str == "-ddr") {
            if (i+1 < argc) {
                input = arg[i+1];
                std::stringstream nStream(input);
                std::string matchOutput;
                std::regex numberPattern(R"(^-?\d+(\.\d+)?$)"); // Matches integers and doubles
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                double dr = std::stod(matchOutput);
            pp::hydrogenSchrodinger::convergenceDeltaRparallel(dr);
            }
        }
        if(str == "--divergenceDeltaRmax" || str == "-ddrm") {
            if (i+1 < argc) {
                input = arg[i+1];
                std::stringstream nStream(input);
                std::string matchOutput;
                std::regex numberPattern(R"(^-?\d+(\.\d+)?$)"); // Matches integers and doubles
                std::getline(nStream, matchOutput, ',');
                if(!std::regex_match(matchOutput, numberPattern)) {
                    std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                    break;
                };
                double rmax = std::stod(matchOutput);
            pp::hydrogenSchrodinger::convergenceDeltaRmaxparallel(rmax);
            }
        }

    }

}