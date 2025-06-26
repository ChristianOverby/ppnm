Exam Project #15: LU Decomposition of a Real Square Matrix

The LU decomposition of a real square matrix is implemented using the Doolittle algorithm.
This algorithm exhibits O(n³) complexity due to the triple-nested for loops, which construct the upper triangular
matrix U row by row and the lower triangular matrix L column by column.

This LU decomposition algorithm also includes partial pivoting, which involves rearranging rows so that,
at each pivot index i, the rows from i to n - 1 are searched for the absolute maximum value in column i.
If such a value is found, the rows are swapped.

This partial pivoting algorithm is greedy and does not necessarily provide the best numerical stability.
If a pivot results in a zero value in U (U = 0), no fallback technique is implemented to handle this, 
and the decomposition fails silently.
One could implement fallbacks such as full pivoting or even semi-random pivoting in such cases.

If the decomposition fails silently, no meaningful results will be produced, as division by zero will 
return an infinite (inf) value.
It is therefore up to the user to detect that a valid solution was not obtained.

LU Class Overview
Constructor:
    The constructor performs the Doolittle partial-pivoting LU decomposition on the supplied matrix (A).

Methods:
    Solve:
    Takes a vector (b) and solves the equation A * x = b.

    Determinant:
    Calculates and returns the determinant of A.

    Inverse:
    Calculates and returns the inverse of A (A⁻¹).

The class also includes getter methods for L, U, P, and the pivoted matrix A_p, where P is a pivot vector.


The LU decomposition has the same time complexity as the QR decomposition; however, QR involves more 
computationally intensive operations such as square roots and normalization.
A plot comparing the complexity of QR and LU factorization is generated as plot.benchmark.svg.



Doing make on this project executes the main file as:
./main -rut > Output.txt
This runs unit tests for LU decomposition, solving, and inversion on semi-random matrices, and prints relevant information.
It also generates a benchmark file for LU and QR decomposition on matrices of varying sizes. 
The procedure is described in greater detail in the Makefile, if needed.


The main file can be run with arguments
-rut or --runUnitTest
    Runs the unit tests for LU decomposition and prints the results to the console.
-ssqQR n,m or --sizeSquareQR n,m
    This generates a n x n square matrix and perfoms QR decomposition on it. This is done m number of times
-ssqLU n,m or --sizeSquareLU n,m
    This generates a n x n square matrix and perfoms LU decomposition on it. This is done m number of times
--file FILENAME or -f FILENAME
    Test LU decomp on a custom matrix defined in a .csv style way with " " between row indicies and \n for coloumns
    (example matrix is provided as matrix.csv)


This algorithm fails quietly, which is not very user-friendly, and this could definitely be improved.
Additional pivoting techniques could be implemented when a U = 0 pivot is encountered,
which might help resolve certain edge cases.
However, the LU decomposition performs as intended and fulfills the required functionality.
Therefore, I would rate this project, assuming the points are awarded strictly 
based on adherence to the project requirements. 
10/10

