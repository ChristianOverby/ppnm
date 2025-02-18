#include <iostream>
#include <vector>
#include <string>
#include<iomanip>
#include <sstream>
#include "includes/genlist.hpp"

void printGenListVecDoubleAsExponetials(const userdef::GenList<std::vector<double>>& genlist) 
{
    std::cout << "Values in exponential format" << std::endl;
    for (const std::vector<double>& vec : genlist) 
    {
        for (const double& x : vec) 
        {
            std::cout << " " << std::scientific << std::setprecision(4) << x << "\t";
        }
        std::cout << std::endl;
    }
}


int main() {
    userdef::GenList<std::vector<double>> list;
    std::string line;
    double x;
    // save the standard input data in a GenList in vectors of type double.
    // could also save input data as a GenList in a Genlist of type double.
    while(std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::vector<double> vecNumbers;
        while(iss >> x) 
        {
            vecNumbers.push_back(x);  // basically just my add method i guess.
        }
        list.add(vecNumbers);
    }

    printGenListVecDoubleAsExponetials(list);

    std::cout << "Removing index 1 of the GenList" << std::endl;
    list.remove(1);
    
    printGenListVecDoubleAsExponetials(list);

    return 0;
}