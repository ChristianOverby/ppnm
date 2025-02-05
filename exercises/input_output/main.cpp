#include<iostream>
#include<string>
#include<cmath>
int main(int argc, char* arg[]) {
    std::string str;
    for (int i = 1; i< argc; i++) {
        str += arg[i];
    };

    //if (arg[1] == "-numbers") {std::cout << arg[1] << std::endl;};
    std::cout << str << std::endl;
    return 0;
};
