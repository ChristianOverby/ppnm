#include "lsfitter.hpp"
#include "../includes/matrix.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

pp::vector logSpace(const pp::vector& y) {
    pp::vector logy(y.size());
    for (int i = 0; i < y.size(); ++i) {
        logy[i] = std::log(y[i]);
    }
    return logy;
}

pp::vector uncPropLog(const pp::vector& y, const pp::vector& dy) {
    pp::vector dylog(dy.size());
    for (int i = 0; i < dy.size(); ++i) {
        dylog[i] = dy[i]/y[i];
    }
    return dylog;
}

int main() {

    // Get the data from the data.csv file
    std::ifstream file("data.csv");
    if(!file.is_open()) {
        std::cerr << "Could not open data.csv" << std::endl;
        return 1;
    }
    std::vector<pp::vector> data;
    std::string line;
    int lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n'); // Counts the amount of lines in the file
    file.clear(); // Clear the end-of-file flag
    file.seekg(0, std::ios::beg); // Move the file pointer to the beginning
    pp::vector v1(lines);
    pp::vector v2(lines);
    pp::vector v3(lines);
    data.emplace_back(v1);
    data.emplace_back(v2);
    data.emplace_back(v3);
    data[0][0] = 1;
    int i = 0;
    while (std::getline(file,line)) {
        std::stringstream ss(line);
        std::string value;
        int colIndex = 0;
        while (std::getline(ss, value, ' ')) {
            data[colIndex++][i] = (std::stod(value));
        }
        i++;
    }
    file.close();
     
    pp::vector x = data[0];
    pp::vector y = data[1];
    pp::vector dy = data[2];
    // hate this method of import but im not changing it

    // Take logarithm of y
    pp::vector logy = logSpace(y);
    pp::vector logdy = uncPropLog(y, dy);

    // Basis functions for linear fit: ln(y) = ln(a) - lambda * t
    std::vector<std::function<double(double)>> fs = {
        [](double) { return 1.0; },  // Constant term ln(a)
        [](double t) { return -t; },    // -lambda * t
        //[](double t) { return -t*t;}
    };

    // Fit the data
    std::pair<pp::vector, pp::matrix> fit = pp::ode_ls_fit(fs, x, logy, logdy);
    pp::vector popt = fit.first;
    pp::matrix pcov = fit.second;
    // uncertainties of fit variables
    pp::vector unc(popt.size());
    for (int i = 0; i < popt.size(); ++i) {
        unc[i] = std::sqrt(pcov[i][i]);
    }
    std::cout << "Solution c:\n" << popt << "\nstderr on sol:\n" << unc << std::endl;
    //halflife
    double T = log(2) / popt[1];
    double dT = log(2) / (popt[1] * popt[1]) * unc[1];

    std::cout << "Halflife of ThX:\nT1/2 = " <<std::setprecision(3) << T << " +- "
    << std::setprecision(1) << dT << " days" 
    << "\nT1/2 reference value = 3.6316(23) days" << std::endl;

    

    std::cout << "Covariance matrix pcov:\n" << pcov << std::endl;
    


    return 0;
}