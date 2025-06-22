#include <iostream>
#include <fstream>
#include <string>
#include "minimiser.hpp"
#include <cmath>
#include <sstream>

double rosenbrock(const pp::vector& v) {
    return std::pow(1-v[0],2)+100*std::pow((v[1]-std::pow(v[0],2)),2);
}

double himmelblau(const pp::vector& v){
    return std::pow(std::pow(v[0],2) + v[1] - 11, 2) + std::pow(v[0]+v[1]*v[1]-7,2); 
}

double dev(const pp::vector& v, const pp::vector& E, const pp::vector& sigma, const pp::vector& dsigma) {
    double m, Γ, A, sum = 0;
    m = v[0]; Γ = v[1]; A = v[2];
    for(int i = 0; i < E.size(); i++) {
        double f = A/ (std::pow(E[i]-m,2) + Γ*Γ/4);
        sum += std::pow( (f-sigma[i]) / dsigma[i], 2);
    }
    return sum;
}

int main(int argc, char* arg[]) {

    std::cout << "Part 1: Minimizing rosenbrock and himmelblau" << std::endl;
    // Inital guess for rosenbrock
    pp::vector guessR(2);
    double accR = 1e-4;
    guessR[0] = 0;
    guessR[1] = 0;
    auto result = pp::newton(rosenbrock, guessR, accR);
    std::cout <<"Guess: " << guessR <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;
    guessR[0] = 2;
    guessR[1] = 2;
    result = pp::newton(rosenbrock, guessR, accR);
    std::cout <<"Guess: " << guessR <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;
    guessR[0] = -2;
    guessR[1] = -2;
    result = pp::newton(rosenbrock, guessR, accR);
    std::cout <<"Guess: " << guessR <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;
    guessR[0] = 2;
    guessR[1] = -2;
    result = pp::newton(rosenbrock, guessR, accR);
    std::cout <<"Guess: " << guessR <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;

    std::cout << "Himmelblau function minimisation: \n"
    << "Expected global minima at (3,2), (-3.77931, -3.28319), (-2.80512, 3.13131), (3.58443, -1.84813)"
    << std::endl; 

    pp::vector guessH(2);
    double accH = 1e-4;
    guessH[0] = -2;
    guessH[1] = -2;
    result = pp::newton(himmelblau, guessH, accH);
    std::cout <<"Guess: " << guessH <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;

    guessH[0] = -4;
    guessH[1] = -3;
    result = pp::newton(himmelblau, guessH, accH);
    std::cout <<"Guess: " << guessH <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;

    guessH[0] = -4;
    guessH[1] = 2;
    result = pp::newton(himmelblau, guessH, accH);
    std::cout <<"Guess: " << guessH <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;

    guessH[0] = 3;
    guessH[1] = -3;
    result = pp::newton(himmelblau, guessH, accH);
    std::cout <<"Guess: " << guessH <<"\nFound minima: " << result.first[0] 
              << ", " << result.first[1] << "\n" << "iterations: " << result.second << std::endl;

    std::string str;
    std::string input;
    pp::matrix mat;
    for (int i = 1; i < argc; i++) {
        str = arg[i];
        if(str == "--file" || str == "-f") {
                if (i+1 < argc) {
                input = arg[i+1];
                // Open the file with the data
                std::ifstream file(input);
                if (!file.is_open()) {
                    std::cerr << "Could not open " << input << std::endl;
                    return 1;
                }
                //std::cout << input << std::endl;
                // Read the file line by line
                std::vector<pp::vector> data;
                std::string line;
                int num_columns = 0;

                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    pp::vector row;
                    double value;

                    // Split the line into values
                    while (iss >> value) {
                        row.push_back(value);
                    }

                    // Determine the number of columns from the first line
                    if (num_columns == 0) {
                        num_columns = row.size();
                    }

                    // Check if the row has the correct number of columns
                    if (row.size() != num_columns) {
                        std::cerr << "Error: Inconsistent number of columns in " << input << std::endl;
                        return 1;
                    }

                    // Store the row in the data matrix
                    data.push_back(pp::vector(row));
                }
                // Determine the number of rows and columns
                int num_rows = data.size();

                // Create a matrix and populate it
                mat = pp::matrix(num_rows, num_columns);
                for (int i = 0; i < num_rows; ++i) {
                    for (int j = 0; j < num_columns; ++j) {
                        mat.set(i, j, data[i][j]);
                    }
                }
                std::cout << "\nPart 2: Minimizing the Breit-Wigner function" << std::endl;
                pp::vector E, sigma, dsigma;
                E = mat[0]; sigma= mat[1]; dsigma = mat[2];
                pp::vector guessB(3);
                double accB = 1e-3;
                guessB[0] = 125;
                guessB[1] = 3;
                guessB[2] = 10;

                auto result = pp::newton([&](const pp::vector& v){return dev(v, E, sigma, dsigma);},guessB, accB); 
                std::cout <<"Guess: " << guessB <<"\nFound parameters: " << result.first[0] 
                          << ", " << result.first[1] << ", " << result.first[2]<< "\n" << "iterations: " 
                          << result.second << std::endl;
                file.close();
                std::ofstream file2("params.csv");
                if (!file2.is_open()) {
                    std::cerr << "Could not open " << "params.csv" << std::endl;
                    return 1;
                }
                std::cout << result.first[0] << std::endl;
                file2 << result.first[0] << "\n" << result.first[1] << "\n" << result.first[2];  
                file2.close();
                }
        }
    }

    return 0;
}