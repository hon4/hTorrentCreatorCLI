#include <string>
#include <filesystem>

bool isDIR(const std::string& path){
	return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}
