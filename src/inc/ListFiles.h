#include <iostream>
#include <filesystem>
#include <vector>

std::vector<std::string> ListFiles(std::string& path) {
    std::vector<std::string> ret;
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            ret.push_back(entry.path().lexically_relative(path).string()); //entry.path().string()
        }
    } catch (const std::filesystem::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }

    return ret;
}