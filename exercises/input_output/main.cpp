#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include"includes/functions.hpp"


int main(int argc, char* arg[]) {
    bool noInput = true;
    std::string str;
    std::string input;
    for (int i = 1; i < argc; i++) {
        noInput = false;
        str = arg[i];
        if(str == "--numbers" || str == "-n") {
            if(i+1 < argc) {
                input = arg[i+1];
                udfuncs::processInputNumbers(input);
            }
            else {
                std::cerr << "Not a valid use \n To use: --numbers 2,1,5,2 ";
                }
        }
        if (str == "--input" || str == "-in") {
            if (i+1 < argc) {
                input = arg[i+1];
                std::ifstream myinput(input);
                if (i+2 < argc) {
                    std::string strout = arg[i+2];
                    if (strout == "--output" || strout == "-o") {
                        std::string output = arg[i+3];
                        udfuncs::processInputFile(input, output);
                    }
                }
                else {
                    udfuncs::processInputFile(input);
                }
            }
            else {
                std::cerr << "Not a valid use \n To use: --input \"filename\" (--output \"filename\") ";
                }
        }
    }
    // If no specific argument found, check stdin
    if (noInput) {
        std::string line;
        if (std::getline(std::cin, line)) {
            // Process stdin here
            udfuncs::processInputNumbers(line);
        } else {
            std::cerr << "Error or EOF encountered while reading input" << std::endl;
        }
    }
    
    return 0;
};
