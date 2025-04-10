#include <string>
#include <iostream>

std::string NormalizePath(const std::string& path) {
    if (!path.empty() && path.back() == '/') { //chk if ends with /
        return path;
    }
    return path + '/';
}