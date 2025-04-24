#include <iostream>
#include <cstdint>

void ShowProgressBar(uint64_t& total, uint64_t& cmpl){
	int fill = 32 * cmpl / total;
	std::cout << "\r[";
	for (int i = 0; i < fill; i++) {
		std::cout << "=";
	}
	for (int i = 0; i < 32 - fill; i++) {
		std::cout << " ";
	}
	int percent = 100 * cmpl / total;
	std::cout << "] " << percent << "%" << std::flush;
}