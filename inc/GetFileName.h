#include <iostream>
#include <string>

std::string GetFileName(const std::string& fullPath) {
    size_t lastSlashPos=fullPath.find_last_of("/\\");
    if (lastSlashPos == std::string::npos) {
        return fullPath;
    } else {
        return fullPath.substr(lastSlashPos + 1);
    }
}