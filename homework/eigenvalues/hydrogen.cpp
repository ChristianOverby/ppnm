#include "hydrogen.hpp"
#include "EVD.hpp"
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

namespace pp
{

    // initializes the hamiltonian matrix and the radial coordinate vector r 
    hydrogenSchrodinger::hydrogenSchrodinger(double rmax, double dr) : rmax(rmax), dr(dr)
    {
        pointCount = static_cast<int>(rmax/dr) -1;
        r = pp::vector(pointCount);
        H = pp::matrix(pointCount, pointCount);

        for (int i = 0; i < pointCount; i++) {
            r[i] = dr * (i + 1);
        }
    }

    // Constrtuct the hamiltonian matrix
    void hydrogenSchrodinger::hamiltonian()
    {
        // kinetic nergy frontfactor
        double kf = -0.5 / (dr*dr);
        //Construct kinetic energy matrix
        H.setDiagonal((-2*kf),0); H.setDiagonal(kf*1,1); H.setDiagonal(kf*1,-1);
        for(int i = 0; i < pointCount; i++) {
            H(i,i) = H(i,i) - 1/r[i];
        }
    }

    void hydrogenSchrodinger::solve()
    {
        pp::EVD evd(H);
        pp::vector egValues = evd.w;
        pp::matrix egVectors = evd.V;
        
        // store the eigenvalues for plotting at the same time

        std::ofstream outputFile("eigenvalues.csv");
        std::stringstream buffer;

        for (int i = 0; i < pointCount; i++) {
            outputFile << r[i] << " ";
            for (int j = 0; j < 4; j++) {
                outputFile << egVectors(i, j) / std::sqrt(dr) << " ";  // Normalize
            }
            outputFile << "\n";
        }

        outputFile << buffer.rdbuf();  // Write the entire buffer to the file in one go
        outputFile.close();


    }

    void hydrogenSchrodinger::convergenceDeltaR() {
      std::ofstream outfile("convergenceDeltaR.csv");
      std::stringstream buffer;

      double fixed_rmax = 20;

      for (double dr_test = 0.05; dr_test <= 1; dr_test += 0.05) {
        hydrogenSchrodinger solver(fixed_rmax, dr_test);
        solver.hamiltonian();
        pp::EVD evd(solver.H);
        buffer << dr_test << " " << evd.w[0] << "\n";
      }
      outfile << buffer.rdbuf();
      outfile.close();
    }
    
    void hydrogenSchrodinger::convergenceDeltaRparallel(double dr_p)
    {
      std::ofstream outfile("convergenceDeltaRParallel.csv", std::ios::app);
      std::stringstream buffer;

      double fixed_rmax = 20;

      hydrogenSchrodinger solver(fixed_rmax, dr_p);
      solver.hamiltonian();
      pp::EVD evd(solver.H);
      buffer << dr_p << " " << evd.w[0] << "\n";
      outfile << buffer.rdbuf();
      outfile.close();
    }

    

    void hydrogenSchrodinger::convergenceDeltaRmax() {
      std::ofstream outfile("convergenceDeltaRmax.csv");
      std::stringstream buffer;

      double fixed_dr = 0.1;

      for (double rmax_test = 1; rmax_test <= 20; rmax_test += 0.5) { // Vary rmax
        hydrogenSchrodinger solver(rmax_test, fixed_dr);
        solver.hamiltonian();
        pp::EVD evd(solver.H);
        buffer << rmax_test << " " << evd.w[0] << "\n";
      }

      outfile << buffer.rdbuf();
      outfile.close();
    }

    void hydrogenSchrodinger::convergenceDeltaRmaxparallel(double drmax_p) {
      std::ofstream outfile("convergenceDeltaRmaxParallel.csv", std::ios::app);
      std::stringstream buffer;

      double fixed_dr = 0.1;
      hydrogenSchrodinger solver(drmax_p, fixed_dr);
      solver.hamiltonian();
      pp::EVD evd(solver.H);
      buffer << drmax_p << " " << evd.w[0] << "\n";

      outfile << buffer.rdbuf();
      outfile.close();
    }
}