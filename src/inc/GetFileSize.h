#include <iostream>
#include <fstream>

uint64_t GetFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        return -1; // Return -1 to indicate an error opening the file
    }
    return static_cast<uint64_t>(file.tellg());
}
