#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::ifstream file("studentai10000.txt"); 

    if (!file.is_open()) {
        std::cout << "File not found\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
}