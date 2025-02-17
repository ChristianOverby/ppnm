#include "functions.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <cmath>
#include <fstream>


namespace udfuncs {

    void processInputNumbers(const std::string& input) {
        std::stringstream nStream(input);
        std::string matchOutput;
        std::regex numberPattern(R"(^-?\d+(\.\d+)?$)"); // Matches integers and decimals

        while(std::getline(nStream, matchOutput, ',')) {
            if(!std::regex_match(matchOutput, numberPattern)) {
                std::cerr << "Error: Expected a number as input at:" << "\t" << matchOutput << "\n\t" << " in number inputs:" << "\t" << input << std::endl;
                break;
            };
            double x = std::stod(matchOutput);
            std::cout << "x = " << x << "\t" << "sin(" << x << ") = " << std::sin(x) << "\t" << "cos(" << x << ") = " << std::cos(x) << std::endl;
        }
    }

    void processInputFile(std::string infile, std::string outfile) {
        std::ifstream myinput(infile);
        std::ofstream myoutput(outfile);    
        double x;
        if( myinput.is_open() && myoutput.is_open() ){
            while( myinput >> x ){
                myoutput << x <<" "<<std::sin(x)<<" "<<std::cos(x)<<std::endl;
                }
            }
        else{
            std::cerr << "Error opening files: " << infile << outfile << std::endl;
            // not really needed since the destructor will close the file streams when they go out of scope
            myinput.close();
            myoutput.close();
            return;
            }
        // not really needed since the destructor will close the file streams when they go out of scope
        myinput.close();
        myoutput.close();
        }
    void processInputFile(std::string infile) {
        std::ifstream myinput(infile); 
        double x;
        if(myinput.is_open()){
            while( myinput >> x ){
                std::cout << x <<" "<<std::sin(x)<<" "<<std::cos(x)<<std::endl;
                }
            }
        else{
            std::cerr << "Error opening files: " << infile << std::endl;
            // not really needed since the destructor will close the file streams when they go out of scope
            myinput.close();
            return;
            }
        // not really needed since the destructor will close the file streams when they go out of scope
        myinput.close();
        }
}