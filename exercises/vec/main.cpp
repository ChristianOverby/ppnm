#include"includes/vec.hpp"
#include<fstream>

int main() {
    std::ofstream file("output.txt");
    // if the file is not open, return 1
    if (!file) return 1;
    udvector::vec v1(1.0, 2.0, 3.0);  // First vector (1.0, 2.0, 3.0)
    udvector::vec v2(4.0, 5.0, 6.0);  // Second vector (4.0, 5.0, 6.0)
    
    // Add v1 and v2 using overloaded + operator
    udvector::vec v3 = v1 + v2;

    // Display stuff
    file << "v3(Getter methods): (" << v3.getX() << ", " << v3.getY() << ", " << v3.getZ() << ")" << std::endl;
    file << "v3(toString): " << v3.toString() << std::endl;
    
    file.close();
    return 0;
}