#include<cmath>
#include<iostream>
#include<thread>
#include<fstream>


int main(){
    std::ofstream file("output.txt");
    // if the file is not open, return 1
    if (!file) return 1;
    // largest signed & unsigned int number
    int x = 0;
    unsigned int y = 0;

    // largest signed int number
    for (int i = 2147482624; i>0; i++) {
        x = i;
        // This can be done since signed integers are being used
        if ((i+1)< 0) {
            break;
        }
    }
    // largest unsigned int number
    for (unsigned int i = x*2-2; i>0; i++) { 
        y = i;
        if ((i+1) < i ) {
            break;
        }
    }
    // machine epsilon
    float z = 0.01f;
    double t = 0.01;
    // find the machine epsilon for float
    while (1 + z != 1) {
        z /= 2;
    }
    // find the machine epsilon for double
    while (1 + t != 1) {
        t /= 2;
    }
    // tiny epsilon shenanigans
    float tiny = z;
    double tiny2 = t;
    float a_f = tiny + tiny + 1;
    double a_d = tiny2 + tiny2 + 1;
    float b_f = 1 + tiny + tiny;
    double b_d = 1 + tiny2 + tiny2; 

    // 1.0 eight times
    double d1 = 1.0 + 1.0 + 1.0 + 1.0 + 1.0 + 1.0 + 1.0 + 1.0;
    double d2 = 1.0*8.0;

    // write to file
    file << "largest signed int number: " << x << "\n";
    file << "largest signed int number + 1:  " << x + 1 << "  This is also the smallest number due to the overflow wrap" << "\n";
    file << "largest signed int number + 10: " << x + 10 << "\n";
    file << "+1 larger or smaller? " << (x+1 > x ? "larger" : "smaller") << "\n";
    file << "largest unsigned int number: " << y << "\n";
    file << "largest unsigned int number + 1:  " << y+1 << "\n";
    file << "largest unsigned int number + 10: " << y+10 << "\n";
    file << "+1 larger or smaller? " << (y+1 > y ? "larger" : "smaller") << "\n";
    // more precision is needed to see the difference
    file.precision(37);
    file << "Machine float epsilon:  " << z*2 << "\n";
    file << "Machine double epsilon: " << t*2 << "\n";
    file << "(float) a = tiny + tiny + 1      =" << a_f << "\n";
    file << "(double) a = tiny2 + tiny2 + 1   =" << a_d << "\n";
    file << "(float) a_r = 1 + tiny + tiny    =" << b_f << "\n";
    file << "(double) a_r = 1 + tiny2 + tiny2 =" << b_d << "\n";
    // check for "a==b", "a>1", "b>1"
    file << "float a == float b:   " << (a_f == b_f ? "true" : "false") << "\n";
    file << "double a == double b: " << (a_d == b_d ? "true" : "false") << "\n";
    file << "float a > 1: " << (a_f > 1 ? "true" : "false") << "\n";
    file << "double a > 1: " << (a_d > 1 ? "true" : "false") << "\n";
    file << "float b > 1: " << (b_f > 1 ? "true" : "false") << "\n";
    file << "double b > 1: " << (b_d > 1 ? "true" : "false") << "\n";
    file << "I cannot explain the expressions with any security, i feel that the \"tiny\" epsilon should just be rounded to 0" << "\n";
    file << "It seems as though the tiny epsilon can be added together as long as one is in the domain of their size" << "\n";
    // print d1 & d2 and check for d1 == d2
    file << "d1: " << d1 << "\n";
    file << "d2: " << d2 << "\n";
    file << "d1 == d2: " << (d1 == d2 ? "true" : "false") << "\n";
    file.close();
}