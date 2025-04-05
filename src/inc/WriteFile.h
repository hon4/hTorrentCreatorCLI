#include <iostream>
#include <fstream>
#include <string>

bool WriteFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing\n";
        return false;
    }

    outFile << content;

    outFile.close();

    return true;
}