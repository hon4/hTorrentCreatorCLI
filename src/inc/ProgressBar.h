#include <iostream>
#include <stdint.h>

void ShowProgressBar(uint64_t& total, uint64_t& cmpl){
	uint8_t fill = 32 * cmpl / total;
	std::cout << "\r[";
	for (uint8_t i = 0; i < fill; i++) {
		std::cout << "=";
	}
	for (uint8_t i = 0; i < 32 - fill; i++) {
		std::cout << " ";
	}
	uint8_t percent = 100 * cmpl / total;
	std::cout << "] " << static_cast<int>(percent) << "%" << std::flush;
}
