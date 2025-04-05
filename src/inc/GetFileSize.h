#include <iostream>
#include <fstream>

long GetFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        return -1; // Return -1 to indicate an error opening the file
    }
    return static_cast<long>(file.tellg());
}